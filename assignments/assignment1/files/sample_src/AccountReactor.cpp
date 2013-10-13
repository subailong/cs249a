class AccountReactor : public Account::Notifiee {
public:
	void onAccountHolder() {
	// handle change to account holder
	. . .
	}

void onType() {
	// handle change to type of account
	. . .
	}
void onBalance() {
	// handle change to balance
	. . .
}
static AccountReactor::Ptr AccountReactorIs( Account * a, TImpl * owner ) {
	AccountReactor * m = new AccountReactor(a,owner);
	m->referencesDec(1);
	return m;
}
protected:
	AccountReactor( Account * a, TImpl * owner ) : Account::Notifiee( a ),
	owner_(owner){}
	TImpl * owner_;
}