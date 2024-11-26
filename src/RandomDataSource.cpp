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

#include <RandomDataSource.h>

std::string
RandomDataSource::get_data(std::string code, std::string type,
			   time_t date_from, time_t date_to,
			   std::string airline_iata) {
  std::srand(std::time(nullptr));
  unsigned num_of_entries = rand()%50 + 100;
  std::string data;
  data += "{\n    \"status\": 200,\n    \"success\": true,\n    \"code\": \"" +
    code + "\",\n    \"type\": \"" + type + "\",\n    \"data\": [\n";
  for(unsigned i = 0; i < num_of_entries; i++) {
    std::string indent = "        ";
    data += indent + "{\n";
    {
      {
	indent += "    ";
	data += indent + "\"movement\": {\n";
	int random_airport_index = rand()%airports.size();
	if(airports.at(random_airport_index).code == code)
	  random_airport_index = (random_airport_index + 1)% airports.size();
	{
	  indent += "    ";
	  data += indent + "\"airport\": {\n"; 
	  data += indent + "    \"name\": \"" +
	    airports.at(random_airport_index).name + "\"\n" + indent + "},\n";
	}
	{
	  auto to_string_format = [](int num, int size){
	    std::string s = std::to_string(num), res;
	    while(res.size() < (size-s.size())){
	      res +='0';
	    }
	    return res+s;
	  };
	  data += indent + "\"scheduledTime\": {\n";
	  time_t random_time = time_t (date_from + rand()%86400);
	  std::tm *random_utctime = std::gmtime(&random_time);
	  data += indent + "    \"utc\": \"";
	  data += std::to_string(random_utctime->tm_year+1900) + '-' +
	    to_string_format(random_utctime->tm_mon, 2) + '-' +
	    to_string_format(random_utctime->tm_mday, 2) + " " +
	    to_string_format(random_utctime->tm_hour, 2) + ':' +
	    to_string_format(random_utctime->tm_min, 2);
	  data += "Z\",\n";

	  std::tm *random_localtime = std::localtime(&random_time);
	  data += indent + "    \"local\": \"";
	  data += std::to_string(random_localtime->tm_year+1900) + '-' +
	    to_string_format(random_localtime->tm_mon, 2) + '-' +
	    to_string_format(random_localtime->tm_mday, 2) + " " +
	    to_string_format(random_localtime->tm_hour, 2) + ':' +
	    to_string_format(random_localtime->tm_min, 2) +
	    airports.at(random_airport_index).timezone + '\"' + '\n';
	  data += indent + "},\n";
	}
	//TODO: Randomize this
	data += indent + "\"terminal\": \"C\",\n" + indent +
	  "\"runway\": \"13\",\n" + indent + "\"quality\": [\n" + indent
	  + "    \"Basic\",\n" + indent + "    \"Live\"\n" + indent + "]\n";
	indent.resize(indent.size()-4);
	data += indent + "},\n";
      }
      data += indent + "\"number\": \"DL 364\",\n" + indent +
	"\"callSign\": \"DAL364\",\n" + indent + "\"status\": \"Departed\",\n" +
	indent + "\"codeshareStatus\": \"IsOperator\",\n" + indent +
	"\"isCargo\": false,\n";

      {
	data += indent + "\"aircraft\": {\n";
	indent += "    ";
	data += indent + "\"reg\": \"N361DN\",\n" + indent +
	  "\"modeS\": \"A4105B\",\n" + indent + "\"model\": \"" +
	  aircrafts[rand()%aircrafts.size()] + "\"\n";
	indent.resize(indent.size()-4);
	data += indent + "},\n";
      }
      {
	auto random_airline = airlines.at(rand()%airlines.size());
	data += indent + "\"airline\": {\n";
	indent += "    ";
	data += indent + "\"name\": \"" + random_airline.name + "\",\n" +
	  indent + "\"iata\": \"" + random_airline.iata + "\",\n" + indent +
	  "\"icao\": \"" + random_airline.iaco + "\"\n";
	indent.resize(indent.size()-4);
	data += indent + "},\n";
      }
      indent.resize(indent.size()-4);
      data += indent + "}" + ((i == num_of_entries - 1) ? "\n" : ",\n");
    }
  }
  data += "    ]\n}\n";
  return data;
}
	

