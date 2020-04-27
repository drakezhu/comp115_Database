#pragma once

#include <libpq-fe.h>

/*
 * Indicates the status of various bank operations.
 */
enum BankOpStatus {
    UNDEFINED,
    OK,
    BALANCE_FAILED,
    AUDIT_FAILED,
    TRANSFER_FAILED
};

/*
 * Represents the outcome of a bank operation. The amount is defined only
 * when status = OK.
 */
class BankOpOutcome
{
public:
    BankOpOutcome();
    BankOpOutcome(BankOpStatus status);
    BankOpOutcome(int amount);

    void operator=(const BankOpOutcome& outcome);

    BankOpStatus status() const;

    int amount() const;

private:
    BankOpStatus _status;
    int _amount;
};

/*
 * Return the balance of the given account, in a BankOpOutcome with status OK.
 * If the balance cannot be read, due to a concurrency conflict, return
 * a BankOpOutcome with status BALANCE_FAILED.
 */
BankOpOutcome read_balance(PGconn* connection, int account_id);

/*
 * Transfer the given amount from the account identified by from_id,
 * to the account identified by to_id. Amount is expected to not
 * exceed the from_id account's balance. Return a BankOpOutcome with
 * status OK on success. Return a BankOpOutcome
 * with status TRANSFER_FAILED if the update failed due to a
 * concurrency conflict.
 */
BankOpOutcome transfer(PGconn* connection, int from_id, int to_id, int amount);

/*
 * Return the sum of balances in a BankOpOutcome with status OK. 
 * In case of a concurrency conflict, a BankOpOutcome with status 
 * AUDIT_FAILED is returned.
 */
BankOpOutcome audit(PGconn* connection);
