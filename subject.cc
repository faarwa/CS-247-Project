#include <set>
#include <iostream>
#include "subject.h"
#include "observer.h"

using namespace std;

// method to subscribe an observer to the subject
void Subject::subscribe (Observer *newView) {
    observers_.insert(newView);
}

// method to unsubscribe an observer from a subject
void Subject::unsubscribe (Observer *formerView) {
     observers_.erase(formerView);
}

// method for subject to call notify so the observer can call update
// in this case, the views are observers of the subject model
void Subject::notify() {
  Observers::iterator i;
  for (i = observers_.begin(); i != observers_.end(); ++i) {
  	(*i)->update();
  }
}
