**Problem**

Model simple way for storing money - we will be storing dollars/cents as simple ints for our model.
Idea is to implement various operations on **Money** class - to be able to add/subtract/multiply/divide money by constant.

Please, comment on the correctness of implementations in terms of - operators overloading, copy/move constructors/numbers manipulations and general code style and quality.

I have a few tests passing for my class [here]|(https://gist.github.com/mgalushka/e18280ba06f11d5c6178) - so this is fully functional (except overflow checks - marked as __TODO__ - whould be great if someone recommennds industry standard for overflow/underflow checks which is used everywhere, safe and fast).

**Money.h**


**Money.cpp**
