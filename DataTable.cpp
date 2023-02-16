/*
This example implements a DataTable class that has functions for adding columns and rows, as well as for printing the table. 
The AddColumn function adds a column to the table and stores its name and data type. 
The AddRow function adds a row to the table, where each row is a map of column names to values. 
The Print function prints the table by iterating over the rows and columns and printing the values in tab-separated format.
*/

#include <map>
#include <set>
#include <string>
#include <vector>
#include <iostream>

class DataTable {
 public:
  DataTable() {}

  void AddColumn(const std::string &column_name, const std::string &data_type) {
    column_names_.push_back(column_name);
    data_types_[column_name] = data_type;
  }

  void AddRow(const std::map<std::string, std::string> &row) {
    rows_.push_back(row);
  }

  void Print() const {
    // Print header row
    for (const auto &column_name : column_names_) {
      std::cout << column_name << "\t";
    }
    std::cout << std::endl;

    // Print data rows
    for (const auto &row : rows_) {
      for (const auto &column_name : column_names_) {
        std::cout << row.at(column_name) << "\t";
      }
      std::cout << std::endl;
    }
  }

 private:
  std::vector<std::string> column_names_;
  std::map<std::string, std::string> data_types_;
  std::vector<std::map<std::string, std::string>> rows_; 
  
  DataTable SetUnion(const DataTable &other) const {
    DataTable result;

    // Combine the columns of both tables
    std::set<std::string> all_column_names(column_names_.begin(),
                                            column_names_.end());
    all_column_names.insert(other.column_names_.begin(),
                            other.column_names_.end());
    for (const auto &column_name : all_column_names) {
      result.AddColumn(column_name,
                       data_types_.count(column_name) ? data_types_.at(column_name)
                                                      : other.data_types_.at(column_name));
    }

    // Add the rows from both tables
    result.rows_.insert(result.rows_.end(), rows_.begin(), rows_.end());
    result.rows_.insert(result.rows_.end(), other.rows_.begin(), other.rows_.end());

    return result;
  }

  DataTable SetDifference(const DataTable &other) const {
    DataTable result;

    // Combine the columns of both tables
    std::set<std::string> all_column_names(column_names_.begin(),
                                            column_names_.end());
    all_column_names.insert(other.column_names_.begin(),
                            other.column_names_.end());
    for (const auto &column_name : all_column_names) {
      result.AddColumn(column_name,
                       data_types_.count(column_name) ? data_types_.at(column_name)
                                                      : other.data_types_.at(column_name));
    }

    // Add the rows that are in this table but not in the other table
    std::set<std::map<std::string, std::string>> other_rows(other.rows_.begin(),
                                                             other.rows_.end());
    for (const auto &row : rows_) {
      if (!other_rows.count(row)) {
        result.AddRow(row);
      }
    }

    return result;
  }

  DataTable SetIntersection(const DataTable &other) const {
    DataTable result;

    // Combine the columns of both tables
    std::set<std::string> all_column_names(column_names_.begin(),
                                            column_names_.end());
    all_column_names.insert(other.column_names_.begin(),
                            other.column_names_.end());

    for (const auto &column_name : all_column_names) {
      result.AddColumn(column_name,
                       data_types_.count(column_name) ? data_types_.at(column_name)
                                                      : other.data_types_.at(column_name));
    }

    // Add the rows that are in this table but not in the other table
    std::set<std::map<std::string, std::string>> other_rows(other.rows_.begin(),
                                                             other.rows_.end());
    for (const auto &row : rows_) {
      if (other_rows.count(row)) {
        result.AddRow(row);
      }
    }
    
    return result;
  }

};


int main() {
  DataTable table;

  // Add columns
  table.AddColumn("Molecule", "text");
  table.AddColumn("Solubility", "numeric");
  table.AddColumn("Molecular Weight", "numeric");

  // Add rows
  table.AddRow({{"Molecule", "Paracetamol"},
                {"Solubility", "4.97"},
                {"Molecular Weight", "151"}});
  table.AddRow({{"Molecule", "Caffeine"},
                {"Solubility", "5.05"},
                {"Molecular Weight", "194"}});
  table.AddRow({{"Molecule", "Indomethacin"},
                {"Solubility", "0.4"},
                {"Molecular Weight", "358"}});
  table.AddRow({{"Molecule", "Trimethoprim"},
                {"Solubility", "3.14"},
                {"Molecular Weight", "290"}});

  // Print table
  table.Print();

  return 0;
}