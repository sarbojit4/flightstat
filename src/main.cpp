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

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <unistd.h>

#include <DataParser.h>
#include <RandomDataSource.h>

typedef std::vector<std::string> ParsedDatatype;

int main(int argc, char **argv) {
  RandomDataSource ds;
  while(1){
    DataParser data_parser;
    data_parser.parse(ds.get_data("ARN", "departure", std::time(nullptr),
				  std::time(nullptr)-86400));
    
    sleep(10);    /* Run Passes */
  }
}

 
