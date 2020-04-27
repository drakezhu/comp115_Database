#include <stdlib.h>
#include <stdio.h>
#include <libpq-fe.h>
#include <sys/param.h>
#include "txn.h"
#include "db.h"

BankOpOutcome::BankOpOutcome()
    : _status(UNDEFINED)
{}

BankOpOutcome::BankOpOutcome(BankOpStatus status)
    : _status(status)
{}

BankOpOutcome::BankOpOutcome(int amount)
    : _status(OK),
      _amount(amount)
{}

void BankOpOutcome::operator=(const BankOpOutcome& outcome)
{
    _status = outcome._status;
    _amount = outcome._amount;
}

BankOpStatus BankOpOutcome::status() const
{
    return _status;
}

int BankOpOutcome::amount() const
{
    return _amount;
}

/*
 * Return true (non-zero) if balance was updated, false (zero) otherwise.
 */
static int update_balance(PGconn* connection, int account_id, int amount)
{
    // Run SQL to increment balance by amount.
    return -1;
}

BankOpOutcome read_balance(PGconn* connection, int account_id)
{
    // Run SQL to read balance of account.
    return -1;
}

BankOpOutcome transfer(PGconn* connection, int from_id, int to_id, int amount)
{
    // Update smaller account id first to avoid deadlock.
    int ok = 1;
    if (from_id < to_id) {
        ok = ok && update_balance(connection, from_id, -amount);
        ok = ok && update_balance(connection, to_id, amount);
    } else {
        ok = ok && update_balance(connection, to_id, amount);
        ok = ok && update_balance(connection, from_id, -amount);
    }
    return ok ? BankOpOutcome(OK) : BankOpOutcome(TRANSFER_FAILED);
}

BankOpOutcome audit(PGconn* connection)
{
    // Run SQL to compute sum of balances.
    return -1;
}
