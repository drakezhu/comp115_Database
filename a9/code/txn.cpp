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
    static const char* UPDATE_BALANCE =
        "update account set balance = balance + $2 where account_id = $1";
    
    char str_account_id[256],str_amount[256];
    sprintf(str_account_id, "%d", account_id);
    sprintf(str_amount, "%d", amount);
    
    const char* params[] = {str_account_id, str_amount};
    int res = update(connection, UPDATE_BALANCE, 2, params);
        if (res >= 0) {
	    return 1;
        }
    return 0;
}

BankOpOutcome read_balance(PGconn* connection, int account_id)
{
    
    char sql[256];
    
    sprintf(sql, "select balance from account where account_id = %d", account_id);
    
    PGresult * res = query(connection, sql, 0, NULL);
    return BankOpOutcome(atoi(PQgetvalue(res, 0, 0)));
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
    static const char* AUDIT_BALANCE =
        "select sum(balance) from account";

    PGresult * res = query(connection, AUDIT_BALANCE, 0, NULL);
    
    //printf("res: %s", PQgetvalue(res, 0, 0));
    return BankOpOutcome(atoi(PQgetvalue(res, 0, 0)));
}
