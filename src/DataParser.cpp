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

#include <iostream>
#include <DataParser.h>

bool DataParser::parse(const std::string &data){
  auto status_pos = data.find("status");
  auto success_pos = data.find("success",status_pos);
  if(data[status_pos+9] != '2' ||
     data[status_pos+10] != '0' ||
     data[status_pos+11] != '0' ||
     data[success_pos+10] != 't' ||
     data[success_pos+11] != 'r' ||
     data[success_pos+12] != 'u' ||
     data[success_pos+13] != 'e'){
    std::cout << "Unable to get data\n";
    return false;
  }
  auto pos = data.find("{",success_pos+65);
  for(; pos != std::string::npos && pos < data.size();){
    pos += 14;
    if(data.find("\"movement\"",pos) != pos) {
      std::cout << "Cannot parse data. Data format is different\n";
      return false;
    }
    pos += 30;
    if(data.find("\"airport\"",pos) != pos) {
      std::cout << "Cannot parse data. Data format is different\n";
      return false;
    }
    pos += 33;
    if(data.find("\"iata\"",pos) != pos) {
      std::cout << "Cannot parse data. Data format is different\n";
      return false;
    }
    pos += 9;
    DataType row;
    row.dest_iata = data.substr(pos, 3);
    pos = data.find("}",pos+20) + 19;
    if(data.find("\"scheduledTime\"",pos) != pos) {
      std::cout << data[pos+4]<< "Cannot parse data. Data format is different\n";
      return false;
    }
    pos += 39;
    if(data.find("\"utc\"",pos) != pos) {
      std::cout << "Cannot parse data. Data format is different\n";
      return false;
    }
    row.utc_time = data.substr(pos + 8, 17);
    auto row_end = data.find("\n        }", pos + 25);
    if(row_end == std::string::npos) {
      std::cout << "Cannot parse data. Data format is different\n";
      return false;
    }
    pos = data.find("\"status\"", pos + 25);
    if(pos > row_end) {
      std::cout << "Cannot parse data. Data format is different\n";
      return false;
    }
    row.status = data[pos + 11] == 'D' ? DataType::Departed : DataType::Arrived;
    pos = data.find("\"isCargo\"", pos + 21);
    row.flight_type = data.substr(pos + 11, 4) == "true" ? DataType::Cargo :
      DataType::Passeneger;
    pos = data.find("\"aircraft\"", pos + 20);
    if(pos > row_end) {
      std::cout << "Cannot parse data. Data format is different\n";
      return false;
    }
    pos = data.find("\"model\"", pos + 20);
    if(pos > row_end) {
      std::cout << "Cannot parse data. Data format is different\n";
      return false;
    }
    pos += 10;
    while(data[pos+1] != '\n') row.aircraft_model += data[pos++];
    pos = data.find("\"airline\"", pos + 20);
    if(pos > row_end) {
      std::cout << "Cannot parse data. Data format is different\n";
      return false;
    }
    pos = data.find("\"iata\"", pos + 20);
    if(pos > row_end) {
      std::cout << "Cannot parse data. Data format is different\n";
      return false;
    }
    row.airline_iata = data.substr(pos + 9, 2);
    pos = data.find("{", row_end);
    parsed_data.push_back(std::move(row));
    if(pos == std::string::npos) break;
  }
  return true;
}
