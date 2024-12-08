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

// std::string dest_iata;
//     std::string utc_time;
//     enum Status {Arrived, Departed} status;
//     enum FlightType {Passeneger, Cargo} flight_type;
//     std::string aircraft_model;
//     std::string airline_iata;

#include <DataPass.h>

bool DataPass::initialize(){
  if(sess != nullptr) return true;
  std::ifstream dbconfig;
  dbconfig.open("databaseconfig");
  if(!dbconfig.is_open()){
    std::perror("Error opening databaseconfig file: ");
    return false;
  }
  std::string username, password;
  getline(dbconfig, username);
  getline(dbconfig, password);
  if(username.substr(0,6) != "User: " || password.substr(0,10) != "Password: "){
    std::cout << "Database config file is ill formed\n";
    return false;
  }
  username.erase(0,7);
  username.pop_back();
  password.erase(0,11);
  password.pop_back();
  try {
    sess = std::unique_ptr<mysqlx::Session>
      (new mysqlx::Session("localhost", 33060, username, password));
    {
      mysqlx::RowResult res = sess->sql("show variables like 'version'").execute();
      std::stringstream version;
 
      version << res.fetchOne().get(1).get<std::string>();
      int major_version;
      version >> major_version;
 
      if (major_version < 8)
	{
	  std::cout << "Can work only with MySQL Server 8 or later\n";
	  std::cout << "Done!\n";
	  return false;
	}
    }
    sess->sql("use Flightdata").execute();
    return true;
  }
  catch (const mysqlx::Error &err) {
    std::cout << "ERROR: " << err << "\n";
    return false;
  }
  catch (std::exception &ex) {
    std::cout << "STD EXCEPTION: " << ex.what() << "\n";
    return false;
  }
  catch (const char *ex) {
    std::cout << "EXCEPTION: " << ex << "\n";
    return false;
  }
}

bool DataPass::
flightDepartureStoragePass(const std::string &src,
			   const std::vector<DataParser::DataType> &parsed_data){
  try {
    sess->sql("create table if not exists Departures (src varchar(3), dest varchar(3), type char, model varchar(20), airline varchar(2))").execute();
    for(const auto &row : parsed_data){
      std::string insert_command = "insert into Departures values (";
      insert_command += "'" + src + "', '" + row.dest_iata + "', " +
	(row.flight_type == DataParser::DataType::Passeneger ? "'P', '" : "'C', '") +
        row.aircraft_model + "', '" + row.airline_iata + "')";
      sess->sql(insert_command).execute();
    }
  }
  catch (const mysqlx::Error &err) {
    std::cout << "ERROR: " << err << "\n";
    return false;
  }
  catch (std::exception &ex) {
    std::cout << "STD EXCEPTION: " << ex.what() << "\n";
    return false;
  }
  catch (const char *ex) {
    std::cout << "EXCEPTION: " << ex << "\n";
    return false;
  }
  return true;
}
