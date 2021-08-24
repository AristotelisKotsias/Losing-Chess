# Inquiry

## What did you learn from this assignment?

I revised my knowledge on inheritance and polymorphism. Moreover, I learned about the concept of diamond inheritance which I didn't know.

## What was most difficult to do in this assignement?

The most difficult part of the assignment was to develop the smart AI player.

## The code relies on virtual functions. Could the code have been written without virtual functions?

Without virtual there is not polymorphism, meaning that the subclasses' functions wouldn't be called. Specifically, the way the pieces are made is (i.e. King piece):

```c++
shared_ptr<ChessPiece> cp = make_shared<King>(x, y, true, "king", &board)
```

Without virtual functions, the function that is being invoked is based on the pointer type (ChessPiece) and not the type of object it points to (King).

## Could ChessPiece have been an abstract class?

Yes it could have been. Since there is no piece called ChessPiece in chess, the class could have been abstract and used as an interface.

## There was no separate unit test for each function in this assignement, instead you tested several functions at once with different boards. What are the benefits and drawbacks for this kind of testing compared to unit tests?

The problem with unit tests in this assignment is that there are many different situationms (board postions) and hence it is faster and easier to implement a whole board at once and test that.

## What is the problem with a diamond inheritance?

The "diamond problem" is an ambiguity that arises when two classes B and C inherit from A, and class D inherits from both B and C. If there is a method in A that B and C have overridden, and D does not override it, then which version of the method does D inherit: that of B, or that of C?

## Did you encounter any problem with protected member variables and, if so, how did you solve them?

Yes, they were inaccessible out of the scope of the class even from the childern of the parent class. The problem was solved by declaring the classes that wanted to access the protected member variables as "friend" inside the ChessPiece class.


## Create a queen object and try to set the unnecessaryInt in ChessPiece. What happens?

If the inheritance from ChessPiece to Rook and the inheritance from ChessPiece to Bishop are not marked as virtual, ambiguity problem arises and unnecessaryInt can't be set.

## Think about if it would be better if the queen had a bishop and a rock (as members) instead of inherited from them?

No, the code would be less maintainable. Moreover, queen can be thought as combination of Rook and Bishop and therefore it makes more sense to inherit from them.

## How many test boards will you need to be sure your functions work correctly?

Only one board where I would have all type of pieces of both players in specific positions in order to validate each function.
