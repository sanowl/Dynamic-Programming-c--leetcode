import pandas as pd

def combine_two_tables(person: pd.DataFrame, address: pd.DataFrame) -> pd.DataFrame:
    """
    LeetCode Solution: Combine two tables using LEFT JOIN
    
    Args:
        person: DataFrame with columns [personId, lastName, firstName]
        address: DataFrame with columns [addressId, personId, city, state]
    
    Returns:
        DataFrame with columns [firstName, lastName, city, state]
    """
    # Perform LEFT JOIN on personId
    result = person.merge(address, on='personId', how='left')
    
    # Select and reorder required columns
    return result[['firstName', 'lastName', 'city', 'state']]

# Alternative solution using explicit LEFT JOIN syntax
def combine_two_tables_alt(person: pd.DataFrame, address: pd.DataFrame) -> pd.DataFrame:
    """
    Alternative solution with more explicit column handling
    """
    # Left join person with address
    result = pd.merge(person, address, on='personId', how='left')
    
    # Select only the required columns in the correct order
    return result[['firstName', 'lastName', 'city', 'state']]

# Test function to demonstrate the solution
def test_solution():
    """
    Test the solution with the provided example
    """
    # Create test data
    person_data = {
        'personId': [1, 2],
        'lastName': ['Wang', 'Alice'],
        'firstName': ['Allen', 'Bob']
    }
    
    address_data = {
        'addressId': [1, 2],
        'personId': [2, 3],
        'city': ['New York City', 'Leetcode'],
        'state': ['New York', 'California']
    }
    
    person_df = pd.DataFrame(person_data)
    address_df = pd.DataFrame(address_data)
    
    print("Input DataFrames:")
    print("\nPerson table:")
    print(person_df)
    print("\nAddress table:")
    print(address_df)
    
    # Test both solutions
    result1 = combine_two_tables(person_df, address_df)
    result2 = combine_two_tables_alt(person_df, address_df)
    
    print("\nOutput (Main solution):")
    print(result1)
    
    print("\nOutput (Alternative solution):")
    print(result2)
    
    # Verify both solutions produce the same result
    print(f"\nBoth solutions match: {result1.equals(result2)}")
    
    return result1

# MySQL Solution - For LeetCode Submission
def show_mysql_solution():
    """
    MySQL solution for LeetCode
    """
    mysql_query = """
# Write your MySQL query statement below
SELECT 
    p.firstName,
    p.lastName,
    a.city,
    a.state
FROM Person p
LEFT JOIN Address a ON p.personId = a.personId;
    """
    
    print("MySQL Solution for LeetCode:")
    print(mysql_query)

# SQL equivalent for reference  
def show_sql_equivalent():
    """
    Show the equivalent SQL query for reference
    """
    sql_query = """
    SELECT 
        p.firstName,
        p.lastName,
        a.city,
        a.state
    FROM Person p
    LEFT JOIN Address a ON p.personId = a.personId;
    """
    
    print("Equivalent SQL Query:")
    print(sql_query)

# Explanation of the solution
def explain_solution():
    """
    Explain the pandas solution approach
    """
    explanation = """
    Solution Explanation:
    ====================
    
    1. LEFT JOIN Operation:
       - We use pd.merge() with how='left' to perform a LEFT JOIN
       - This keeps ALL rows from the Person table (left table)
       - Matches with Address table where personId exists
       - For non-matching rows, fills with NaN (equivalent to NULL in SQL)
    
    2. Column Selection:
       - Select only the required columns: firstName, lastName, city, state
       - Maintain the correct order as specified in the problem
    
    3. Key Points:
       - LEFT JOIN ensures we don't lose any person records
       - Missing address data becomes NaN (pandas equivalent of NULL)
       - The 'on' parameter specifies the join key (personId)
    
    4. pandas vs SQL:
       - pd.merge(how='left') ≡ LEFT JOIN in SQL
       - NaN values ≡ NULL values in SQL
       - DataFrame column selection ≡ SELECT clause in SQL
    """
    
    print(explanation)

# Advanced example with more data
def advanced_example():
    """
    Test with more complex data to show edge cases
    """
    # More complex test data
    person_data = {
        'personId': [1, 2, 3, 4, 5],
        'lastName': ['Wang', 'Alice', 'Smith', 'Johnson', 'Brown'],
        'firstName': ['Allen', 'Bob', 'John', 'Jane', 'Charlie']
    }
    
    address_data = {
        'addressId': [1, 2, 3],
        'personId': [2, 4, 6],  # Note: personId 6 doesn't exist in Person table
        'city': ['New York City', 'Los Angeles', 'Chicago'],
        'state': ['New York', 'California', 'Illinois']
    }
    
    person_df = pd.DataFrame(person_data)
    address_df = pd.DataFrame(address_data)
    
    print("Advanced Example:")
    print("\nPerson table:")
    print(person_df)
    print("\nAddress table:")
    print(address_df)
    
    result = combine_two_tables(person_df, address_df)
    
    print("\nResult:")
    print(result)
    
    print("\nObservations:")
    print("- Persons 1, 3, 5 have no address → city and state are NaN")
    print("- Person 2, 4 have addresses → city and state are populated")
    print("- Address for personId 6 is ignored (no matching person)")

if __name__ == "__main__":
    print("=== LeetCode 75: Combine Two Tables ===\n")
    
    # Run the main test
    result = test_solution()
    
    print("\n" + "="*50 + "\n")
    
    # Show SQL equivalent
    show_sql_equivalent()
    
    print("\n" + "="*50 + "\n")
    
    # Explain the solution
    explain_solution()
    
    print("\n" + "="*50 + "\n")
    
    # Advanced example
    advanced_example()