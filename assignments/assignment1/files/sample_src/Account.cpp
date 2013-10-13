//Notifiee Example
class Account : public NamedInterface {
public:
	class Notifiee;
	Customer const * accountHolder() const { return accountHolder_; }
	enum Type {
	savings_ = 1,
	chequing_ = 2,
	};

	Type type() const { return type_; }
	U32 balance() const { return balance_; }
	void balanceIs( U32 );
	Account::Notifiee * notifiee() const { return notifiee_; }

protected:
	Customer* accountHolder_;
	Type type_;
	U32 balance_;
	void notifieeIs( Account::Notifiee * n ) const {
	Account* me = const_cast<Account*>(this);
	me->notifiee_ = n;
	}
	friend class BaseNotifiee<Account>;
	Account::Notifiee * notifiee_;
};

class Account::Notifiee : public NamedInterface::Notifiee {
	public:
	virtual void onAccountHolder() = 0;
	virtual void onType() = 0;
	virtual void onBalance() = 0;
	Notifiee( Account * a ) : NamedInterface::Notifiee( a ) {}
};

void
Account::balanceIs( U32 newBalance ) {
	if( newBalance == balance_ ) return;
	balance_ = newBalance;
	if( notifiee_ ) try {
		notifiee_->onBalance();
	}
	catch(...) {
	try {
		notifiee_->onNotificationException(balance__);
	}
	catch(...){}
	}
}