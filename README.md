This is for testing and demonstration purpose.
I have implemented an Incomplete Version for a Filter Iterator for the Filesystem Library for C++20[c++2a].
The main Goal is to have a Filter Iterator calling a Lambda or std::function<> object in order to determine if a directory_entry is suitable or not.
We can filter for Size, Filext, Type or any other File/Entry Attribute or even call a more complex mechanism within the Process.
The Filesystem Library is very basic in C++20 and need to be extended by the Library User to fit complex purposes.
Since many File operation are OS or Filesystem dependend this would probably require quite a lot of specific implementation code.