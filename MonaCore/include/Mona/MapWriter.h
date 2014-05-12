/*
Copyright 2014 Mona
mathieu.poux[a]gmail.com
jammetthomas[a]gmail.com

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License received along this program for more
details (or else see http://www.gnu.org/licenses/).

This file is a part of Mona.
*/

#pragma once

#include "Mona/Mona.h"
#include "Mona/DataWriter.h"

namespace Mona {

template<class MapType>
class MapWriter : public DataWriter, public virtual Object {
public:
	MapWriter(MapType& map) : _map(map),_size(0),_isProperty(false) {}
	void beginObject(const std::string& type = "", bool external = false) {}
	void endObject() {}

	void writePropertyName(const std::string& value) { _property = value; _isProperty=true; }

	void beginArray(UInt32 size) {}
	void endArray(){}

	void writeDate(const Date& date) { set(date.toString(Date::SORTABLE_FORMAT,_buffer)); }
	void writeNumber(double value) { set(String::Format(_buffer, value)); }
	void writeString(const std::string& value) { set(value); }
	void writeBoolean(bool value) { set( value ? "true" : "false");}
	void writeNull() { set("null"); }
	void writeBytes(const UInt8* data, UInt32 size) { set((const char*)data, size); }

	UInt32 size() const { return _size; }
	UInt32 count() const { return _map.count(); }
	

	void   clear() { _map.clear(); _isProperty = false; _property.clear(); _size = 0; DataWriter::clear(); }
private:
	template <typename ...Args>
	void set(Args&&... args) {
		if (_isProperty) {
			_map[_property].assign(args ...);
			_isProperty = false;
		} else {
			_property.assign(args ...);
			_map[_property].clear();
		}
		_property.clear();
	}

	std::string					_property;
	bool						_isProperty;

	MapType&					_map;
	std::string					_buffer;
	UInt32						_size;
};



} // namespace Mona