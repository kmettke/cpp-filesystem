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
#include <functional>

namespace hynodeva {
    namespace filesystem {
	using FileStatusMask = unsigned int;
	enum FileStatus : unsigned int
	{
	    exists		= (1u <<0),
	    regular_file 	= (1u <<1),
	    directory		= (1u <<2),
	    symlink		= (1u <<3),
	    fifo		= (1u <<4),
	    socket		= (1u <<5),
	    block_file		= (1u <<6),
	    character_file	= (1u <<7),
	    other		= (1u <<8),
	    unknown		= (1u <<10),
	    none		= (1u <<11)
	};
	struct FileProperties
	{
	    public:
	    std::filesystem::path	path;
	    FileStatusMask		status;
	    FileStatus from_file_type(std::filesystem::file_type &b)
	    {
		switch(b)
		{
		    case std::filesystem::file_type::not_found:
			break;
		    case std::filesystem::file_type::regular:
			return FileStatus::regular_file;
			break;
		}
		return FileStatus::none;
	    }
	    FileProperties& operator|(const std::filesystem::file_type ft)
	    {
		return *(this);
	    }
	    FileProperties& operator|(const FileStatusMask& other)
	    {
		return *(this);
	    }
	};
	struct FileCompare {
	    template<class BASEITERATOR>
	    static bool has_real_size(const BASEITERATOR& el)
	    {
		if(!(((*el).is_regular_file()) || ((*el).is_symlink()) || ((*el).is_other())))
		    return false;
		return true;
	    }
	    template<class BASEITERATOR>
	    static bool file_is_larger_then(unsigned int s,const BASEITERATOR& el)
	    {
		if(!has_real_size(el))
		    return false;
		if((*el).file_size()>s)
		    return true;
		return false;
	    }
	    template<class BASEITERATOR>
	    static bool file_is_smaller_then(unsigned int s,const BASEITERATOR& el)
	    {
		if((!file_is_larger_then(s,el)) && (!file_has_equal_size(s,el)))
		    return true;
		return false;
	    }
	    template<class BASEITERATOR>
	    static bool file_has_equal_size(unsigned int s,const BASEITERATOR& el)
	    {
		if(!has_real_size(el))
		    return false;
		if((*el).file_size()==s)
		    return true;
		return false;
	    }
	};

template <class BASEITERATOR,typename B,typename CONSTRUCTPARAM>
class filter_iterator : public BASEITERATOR
{
    public:
    using COMPAREFUNCSIGNATURE = std::function<bool(const BASEITERATOR&)>;
    private:
    const COMPAREFUNCSIGNATURE& compfunc;
    const COMPAREFUNCSIGNATURE& dummyitemselect = [](const BASEITERATOR& b){return false;};
    const bool isdummy;
    public:
    static bool defaultcompare(const BASEITERATOR&)
    {
	return true;
    };
    public:
    explicit filter_iterator(const CONSTRUCTPARAM &p,const COMPAREFUNCSIGNATURE& compfunc_)
    :
    BASEITERATOR(p),
    compfunc(compfunc_),
    isdummy(false)
    {
//	compfunc = compfunc_;
    }
    filter_iterator()
    :
    BASEITERATOR(),
//If we work with decltype Function Signatures we cannot initialize that properly, so we can only compile code with fpermissive at this point
// to work around that i have made a dummy lambda withtin the template class and defined the comparefunction with a "hard" signature. If U want to call some more complex
//you will need a wrapper function suiting the hard function signature and call your custom filter function from there.
    compfunc(dummyitemselect),
    isdummy(true)
//    compfunc(filter_iterator<BASEITERATOR,B,CONSTRUCTPARAM>::defaultcompare)
    {
    }

    BASEITERATOR& operator++()
    {
	if(isdummy)
	    return *this;
	std::error_code ec;
	return increment(ec);
    }

    BASEITERATOR& increment( std::error_code& ec )
    {
	if(isdummy)
	    return *this;
	bool m_end=false;
	while(!m_end)
	{
	    BASEITERATOR::increment(ec);
	    if(*this == filter_iterator<BASEITERATOR,B,CONSTRUCTPARAM>())
	    {
		//we reached the end of the iteration
//		std::cout << "end" <<std::endl;
		return *this;
	    }
	    if(compfunc((BASEITERATOR)*this))
	    {
		m_end=true;
	    }
	}
	return *this;
    }

    const B& operator*() const
    {
	return BASEITERATOR::operator*();
    }
    const bool operator==(const filter_iterator<BASEITERATOR,B,CONSTRUCTPARAM> & other) const
    {
	return (BASEITERATOR(*this)==(other));
    }
};
template<class BASEITERATOR,typename B,class CONSTRUCTPARAM>
filter_iterator<BASEITERATOR,B,CONSTRUCTPARAM> begin(filter_iterator<BASEITERATOR,B,CONSTRUCTPARAM> it) noexcept
{
    return it;
};

template<class BASEITERATOR,typename B,class CONSTRUCTPARAM>
filter_iterator<BASEITERATOR,B,CONSTRUCTPARAM> end(const filter_iterator<BASEITERATOR,B,CONSTRUCTPARAM> it) noexcept
{
    return filter_iterator<BASEITERATOR,B,CONSTRUCTPARAM>();
};

    }
}
