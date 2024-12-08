/* Copyright (C) Sarbojit Das
 *
 * This file is part of FlightStat.
 *
 * FlightStat is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FlightStat is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef DATA_PASS_H
#define DATA_PASS_H

#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <mysqlx/xdevapi.h>
#include <vector>

#include <DataParser.h>

class DataPass {
 public:
  bool initialize();
  bool flightDepartureStoragePass(const std::string &src,
				  const std::vector<DataParser::DataType> &parsed_data);
 private:
  std::unique_ptr<mysqlx::Session> sess = nullptr;
};
#endif
