#ifndef MVC_SUBJECT_H
#define MVC_SUBJECT_H

#include <set>


class Observer;

// class declaration of subject
class Subject {
public:
       void subscribe( Observer* );			// method to subscribe an observer to the subject
       void unsubscribe( Observer* );			// method to unsubscribe an observer from the subject

protected:
       void notify();					// protected member function the subject (model) notifies the observer (views) to update

private:
       typedef std::set< Observer* > Observers;		// private member set of observers
       Observers observers_;				// private member observers
};


#endif
