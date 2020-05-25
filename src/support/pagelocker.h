// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_ALLOCATORS_PAGELOCKER_H
#define BITCOIN_ALLOCATORS_PAGELOCKER_H

#include <map>

#include <support/cleanse.h>

#include <boost/thread/mutex.hpp>
#include <boost/thread/once.hpp>

// Thread-safe class to keep track of locked (ie, non-swappable) memory pages.
template <class Locker>
class LockedPageManagerBase
{
public:
    LockedPageManagerBase(size_t page_size):
        page_size(page_size)
    {
        // Determine bitmask for extracting page from address
        assert(!(page_size & (page_size-1))); // size must be power of two
        page_mask = ~(page_size - 1);
    }

    ~LockedPageManagerBase()
    {
        assert(this->GetLockedPageCount() == 0);
    }

    // For all pages in affected range, increase lock count
    void LockRange(void *p, size_t size)
    {
        boost::mutex::scoped_lock lock(mutex);
        if(!size) return;
        const size_t base_addr = reinterpret_cast<size_t>(p);
        const size_t start_page = base_addr & page_mask;
        const size_t end_page = (base_addr + size - 1) & page_mask;
        for(size_t page = start_page; page <= end_page; page += page_size)
        {
            Histogram::iterator it = histogram.find(page);
            if(it == histogram.end()) // Newly locked page
            {
                locker.Lock(reinterpret_cast<void*>(page), page_size);
                histogram.insert(std::make_pair(page, 1));
            }
            else // Page was already locked; increase counter
            {
                it->second += 1;
            }
        }
    }

    // For all pages in affected range, decrease lock count
    void UnlockRange(void *p, size_t size)
    {
        boost::mutex::scoped_lock lock(mutex);
        if(!size) return;
        const size_t base_addr = reinterpret_cast<size_t>(p);
        const size_t start_page = base_addr & page_mask;
        const size_t end_page = (base_addr + size - 1) & page_mask;
        for(size_t page = start_page; page <= end_page; page += page_size)
        {
            Histogram::iterator it = histogram.find(page);
            assert(it != histogram.end()); // Cannot unlock an area that was not locked
            // Decrease counter for page, when it is zero, the page will be unlocked
            it->second -= 1;
            if(it->second == 0) // Nothing on the page anymore that keeps it locked
            {
                // Unlock page and remove the count from histogram
                locker.Unlock(reinterpret_cast<void*>(page), page_size);
                histogram.erase(it);
            }
        }
    }

    // Get number of locked pages for diagnostics
    int GetLockedPageCount()
    {
        boost::mutex::scoped_lock lock(mutex);
        return histogram.size();
    }

private:
    Locker locker;
    boost::mutex mutex;
    size_t page_size, page_mask;
    // map of page base address to lock count
    typedef std::map<size_t,int> Histogram;
    Histogram histogram;
};

// OS-dependent memory page locking/unlocking. Defined as policy class to make stubbing for test possible.
class MemoryPageLocker
{
public:
    // Lock memory pages. addr and len must be a multiple of the system page size
    bool Lock(const void *addr, size_t len);

    // Unlock memory pages. addr and len must be a multiple of the system page size
    bool Unlock(const void *addr, size_t len);
};

// Singleton class to keep track of locked memory pages, for use in std::allocator templates.
class LockedPageManager: public LockedPageManagerBase<MemoryPageLocker>
{
public:
    static LockedPageManager& Instance()
    {
        boost::call_once(LockedPageManager::CreateInstance, LockedPageManager::init_flag);
        return *LockedPageManager::_instance;
    }

private:
    LockedPageManager();

    static void CreateInstance()
    {
        static LockedPageManager instance;
        LockedPageManager::_instance = &instance;
    }

    static LockedPageManager* _instance;
    static boost::once_flag init_flag;
};

// Functions for directly locking/unlocking memory objects. Intended for non-dynamically allocated structures.

template<typename T> void LockObject(const T &t) {
    LockedPageManager::Instance().LockRange((void*)(&t), sizeof(T));
}

template<typename T> void UnlockObject(const T &t) {
    memory_cleanse((void*)(&t), sizeof(T));
    LockedPageManager::Instance().UnlockRange((void*)(&t), sizeof(T));
}

#endif // BITCOIN_ALLOCATORS_PAGELOCKER_H
