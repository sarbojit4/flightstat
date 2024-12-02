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

#ifndef DATA_PARSER_H
#define DATA_PARSER_H

#include <string>
#include <vector>

class DataParser{
 public:
  struct DataType {
    std::string dest_iata;
    std::string utc_time;
    enum Status {Arrived, Departed} status;
    enum FlightType {Passeneger, Cargo} flight_type;
    std::string aircraft_model;
    std::string airline_iata;
    std::string to_string() const {
      return "dest: " + dest_iata + ", time: " + utc_time + ", status: " +
	(status == Status::Arrived ? "Arrived" : "Departed") + ", flight_type: " +
	(flight_type == FlightType::Passeneger ? "Passenger" : "Cargo") +
	", model: " + aircraft_model + ", airline_iata: " + airline_iata + "\n";
    }
  };
  std::vector<DataType> parsed_data;
  bool parse(const std::string &data);
};

#endif