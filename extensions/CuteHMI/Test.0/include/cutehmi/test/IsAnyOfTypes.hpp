#ifndef H_EXTENSIONS_CUTEHMI_TEST_0_INCLUDE_CUTEHMI_TEST_ISANYOFTYPES_HPP
#define H_EXTENSIONS_CUTEHMI_TEST_0_INCLUDE_CUTEHMI_TEST_ISANYOFTYPES_HPP

#include <type_traits>

namespace cutehmi {
namespace test {

/**
 * Check if template parameter is one of the types specified by @a TYPES.
 * @tparam T paremeter to check.
 * @tparam TYPES types to check.
 * @return if @a T is of one of the types specified by @a TYPES, structure provides
 * a member constant @a value equal to @p true. Otherwise @a value is @p false.
 *
 * @note implementation comes from https://stackoverflow.com/a/17032517/205955.
 */
template<typename T, typename... TYPES>
struct IsAnyOfTypes:
	std::false_type
{
};

template<typename T, typename TYPE>
struct IsAnyOfTypes<T, TYPE>:
	std::is_same<T, TYPE>
{
};

template<typename T, typename TYPE, typename... TYPES>
struct IsAnyOfTypes<T, TYPE, TYPES...>:
	std::integral_constant<bool, std::is_same<T, TYPE>::value || IsAnyOfTypes<T, TYPES...>::value>
{
};

}
}

#endif

//(c)C: Copyright © 2018-2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
