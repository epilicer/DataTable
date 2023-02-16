class DataTable:

    def __init__(self, columns):
        self.columns = columns
        self.rows = []

    def add_row(self, row):
        if len(row) != len(self.columns):
            raise ValueError("Row must have the same number of elements as columns")
        self.rows.append(row)
    
    def __repr__(self):
        s = '\t'.join(str(c) for c in self.columns) + '\n'
        for row in self.rows:
            s += '\t'.join(str(r) for r in row) + '\n'
        return s
    
    def union(self, other):
        if self.columns != other.columns:
            raise ValueError("Tables have different columns")
        result = DataTable(self.columns)
        result.rows = self.rows.copy()
        for row in other.rows:
            if row not in result.rows:
                result.rows.append(row)
        return result
    
    def intersection(self, other):
        if self.columns != other.columns:
            raise ValueError("Tables have different columns")
        result = DataTable(self.columns)
        for row in self.rows:
            if row in other.rows:
                result.rows.append(row)
        return result
                
    def difference(self, other):
        if self.columns != other.columns:
            raise ValueError("Tables have different columns")
        result = DataTable(self.columns)
        for row in self.rows:
            if row not in other.rows:
                result.rows.append(row)
        return result


# Example usage:
# drugs = DataTable(["Molecule", "Solubility", "Molecular Weight"])
# drugs.add_row(["Paracetamol", 4.97, 151])
# drugs.add_row(["Caffeine", 5.05, 194])
# drugs.add_row(["Indomethacin", 0.4, 358])
# drugs.add_row(["Trimethoprim", 3.14, 290])
# print(drugs)

# Example usage:
drugs_a = DataTable(["Molecule", "Solubility", "Molecular Weight"])
drugs_a.add_row(["Paracetamol", 4.97, 151])
drugs_a.add_row(["Caffeine", 5.05, 194])

drugs_b = DataTable(["Molecule", "Solubility", "Molecular Weight"])
drugs_b.add_row(["Indomethacin", 0.4, 358])
drugs_b.add_row(["Trimethoprim", 3.14, 290])

print("Drugs A:")
print(drugs_a)
print("Drugs B:")
print(drugs_b)

print("Drugs A union Drugs B:")
print(drugs_a.union(drugs_b))
print("Drugs A intersection Drugs B:")
print(drugs_a.intersection(drugs_b))
print("Drugs A difference Drugs B:")
print(drugs_a.difference(drugs_b))

