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

#include <cstdarg>
#include <map>
#include <vector>
#include <ctime>
#include <cassert>
#include <string>

#include <DataSource.h>

#ifndef RANDOM_DATA_SOURCE_H
#define RANDOM_DATA_SOURCE_H

/* Generate random data in the format of FlightLabs API (https://app.goflightlabs.com/) */
class RandomDataSource : public DataSource {
 private:
  struct AirportData {
    std::string code, name, timezone;
    AirportData(std::string _code, std::string _name, std::string _timezone) :
    code(_code), name(_name), timezone(_timezone) {}
  };

  struct AirlineData {
    std::string iaco, iata, name;
    AirlineData(std::string _iaco, std::string _iata, std::string _name) :
    iaco(_iaco), iata(_iata), name(_name) {}
  };
  
  template <typename K, typename T> class ArrayMap {
  public:
    std::map<K, unsigned> themap;
    std::vector<T> thevector;
    const T &at(unsigned i) const {
      assert(i < thevector.size());
      assert(0 <= i);
      return thevector[i];
    }
    T &at(unsigned i) {
      assert(i < thevector.size());
      assert(0 <= i);
      return thevector[i];
    }
    const T &operator[](K key) const {
      const auto it = themap.find(key);
      assert(it != themap.end());
      return thevector[it->second];
    }
    T &operator[](K key) {
      const auto it = themap.find(key);
      assert(it != themap.end());
      return thevector[it->second];
    }
    int size() const { return themap.size(); }
    void insert(T data) {
      themap.emplace(data.code, thevector.size());
      thevector.push_back(data);
    }
    template <typename...Types> void emplace(const K &key, Types... args) {
      themap.emplace(key, thevector.size());
      thevector.emplace_back(key, args...);
    }
  };
  ArrayMap<std::string, AirportData> airports;
  ArrayMap<std::string, AirlineData> airlines;
  std::vector<std::string> aircrafts;
 public:
  std::string get_data(std::string code, std::string type,
		       time_t date_from, time_t date_to,
		       std::string airline_iata = "");
  RandomDataSource() {
    airports.emplace("CDG", "Charles de Gaulle", "+02:00");
    airports.emplace("ARN", "Stockholm Arlanda", "+02:00");
    airports.emplace("CPH", "Copenhagen", "+02:00");
    airports.emplace("OSL", "Oslo", "+02:00");
    airports.emplace("FRA", "Frankfurt", "+02:00");
    airports.emplace("BER", "Berlin Brandenburg", "+02:00");
    airports.emplace("AMS", "Amsterdam", "+02:00");
    airports.emplace("VIE", "Vienna", "+02:00");
    airports.emplace("FCO", "Rome Fiumicino", "+02:00");
    airports.emplace("ZRH", "Zurich", "+02:00");
    airports.emplace("BCN", "Bercelona", "+02:00");
    airports.emplace("MAD", "Madrid–Barajas", "+02:00");
    airports.emplace("MXP", "Milan Malpensa", "+02:00");
    airports.emplace("WAW", "Warsaw Chopin", "+02:00");
    airports.emplace("OPO", "Francisco Sá Carneiro", "+02:00");
    airports.emplace("IST", "Istanbul", "+03:00");

    airlines.emplace("SAS", "SK", "Scandinavian Airlines");
    airlines.emplace("DLH", "LH", "Lufthansa");
    airlines.emplace("KLM", "KL", "KLM");
    airlines.emplace("WZZ", "W6", "Wizzair");
    airlines.emplace("RYR", "FR", "Ryanair");
    airlines.emplace("BXI", "SN", "Brussels Airlines");
    airlines.emplace("FIN", "AY", "Finnair");
    airlines.emplace("NAN", "DH", "Norwegian Air");

    aircrafts.emplace_back("Airbus A320 NEO");
    aircrafts.emplace_back("Boeing 737-700");
    aircrafts.emplace_back("Airbus A220-300");
    aircrafts.emplace_back("Airbus A321");
    aircrafts.emplace_back("Embraer 170");
    aircrafts.emplace_back("Bombardier CRJ900");
    aircrafts.emplace_back("Boeing 737 MAX 8");
    aircrafts.emplace_back("Airbus A319");
    
  }
};
#endif
