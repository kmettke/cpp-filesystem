/**
 * The MIT License (MIT)
 * Copyright (c) 2016 tomykaira
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <fstream>
#include <filesystem>
#include <iostream>
#include "filesystem_filter.hpp"

//this is a reverse testing base implementation
class file_iterator : public std::filesystem::directory_iterator
{
    public:
    explicit file_iterator(const std::filesystem::path &p)
    :
    std::filesystem::directory_iterator(p)
    {
    }
    file_iterator()
    :
    std::filesystem::directory_iterator()
    {
    }
    std::filesystem::directory_iterator& operator++()
    {
	std::error_code ec;
	return this->increment(ec);
    }
    std::filesystem::directory_iterator& increment( std::error_code& ec )
    {
	std::filesystem::directory_iterator::increment(ec);
	if(*this == file_iterator())
	{
	    std::cout << "end" <<std::endl;
	    return *this;
	}
	if((*this)->is_regular_file())
	{
	    std::cout << "file" << std::endl;
	}
	else
	{
	    std::cout << "no file" << std::endl;
	}
	return *this;
    }
    const std::filesystem::directory_entry& operator*() const
    {
	return std::filesystem::directory_iterator::operator*();
    }
    const bool operator==(const file_iterator& other) const
    {
	return (std::filesystem::directory_iterator(*this)==(other));
    }
};

file_iterator begin(file_iterator it) noexcept
{
    return it;
};

file_iterator end(const file_iterator it) noexcept
{
    return file_iterator();
};



int main(int argc, char* argv [])
{
    std::string dirpath = ".";
    if(argc > 1)
    {
	dirpath = std::string(argv[1]);
    }
    std::cout << "file_iterator" <<std::endl;
    for(auto &direl : file_iterator(dirpath))
    {
	std::cout << direl.path() << std::endl;
    }
    std::cout << "template filter iterator, used with lambda compare function" <<std::endl;
    unsigned int minfilesize = 1024;
    auto comp2 = [minfilesize](const std::filesystem::directory_iterator& el)->bool {return hynodeva::filesystem::FileCompare::file_is_larger_then(minfilesize,el);};
    for(auto direl = hynodeva::filesystem::filter_iterator<std::filesystem::directory_iterator,std::filesystem::directory_entry,std::filesystem::path>(dirpath,comp2);direl != file_iterator(); ++direl)
    {
	std::cout << (direl)->path() << std::endl;
    }
    std::cout << "auto for" <<std::endl;
    for(auto &direl : hynodeva::filesystem::filter_iterator<std::filesystem::directory_iterator,std::filesystem::directory_entry,std::filesystem::path>(dirpath,comp2))
    {
	std::cout << (direl).path() << std::endl;
    }

    hynodeva::filesystem::FileStatusMask samplestate = hynodeva::filesystem::FileStatus::exists | hynodeva::filesystem::FileStatus::regular_file;
    std::cout << samplestate << std::endl;

}