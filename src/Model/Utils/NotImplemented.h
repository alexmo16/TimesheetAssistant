#pragma once

#include <stdexcept>

namespace Model
{
	class NotImplemented : public std::logic_error
	{
	public:
		NotImplemented() : std::logic_error( "Function not yet implemented" ){};
	};
} // namespace Model
