2.2.5 Release notes
===================

- Fix build error due to change in OpenSSL 1.1 API
- Add build instructions for Fedora
- Add an option to reqeuest a vanity address
- Add `datacarriersize` option to allow the wallet to accept an arbitrarily 
  large `OP_RETURN`
- Add a `sequence` field to `createrawtransaction`, allowing the user to set
  an arbitrary `nSequence` to the transaction.
