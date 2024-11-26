/* Copyright (C) Sarbojit Das
 *
 * This file is part of FlightStat.
 *
 * FlightStat is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Nidhugg is distributed in the hope that it will be useful, but
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

#include <RandomDataSource.h>

typedef std::vector<std::vector<std::string>> ParsedDatatype;

ParsedDatatype parse_data_FlightLabs(const std::string &data){
  ParsedDatatype res;
  unsigned status_pos = data.find("status");
  unsigned success_pos = data.find("success",status_pos);
  if(data[status_pos+9] != '2' ||
     data[status_pos+10] != '0' ||
     data[status_pos+11] != '0' ||
     data[success_pos+10] != 't' ||
     data[success_pos+10] != 'r' ||
     data[success_pos+10] != 'u' ||
     data[success_pos+10] != 'e'){
    std::cout << "Unable to get data\n";
    return res;
  }

  auto dit = data.begin()+data.find("{",success_pos+20);
  for(; dit != data.end(); dit++){
    while(*dit == ' ' || *dit == '\t' || *dit == '\n' || *dit == '{' || *dit == '}') continue;
  }
  return res;
}

int main(int argc, char **argv) {
  RandomDataSource ds;
  std::cout << ds.get_data("ARN", "departure", std::time(nullptr)-86400, std::time(nullptr));
  // while(1){
  //    ParsedDatatype parsed_data =
  //      parse_data_FlightLabs(ds.get_data(ARN, "departure", std::time(nullptr),
  // 					 std::time(nullptr)-86400));
  //   /* Run Passes */
  // }
}

 
