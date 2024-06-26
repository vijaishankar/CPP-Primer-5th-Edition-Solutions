<details><summary><h1 style = "text-align:center; color:blue">DBMS</h1></summary><pre><a href = "/DBMS/Database.cpp">Database.cpp</a>        <a href = "/DBMS/Query.cpp">Query.cpp</a>           <a href = "/DBMS/Query.h">Query.h</a>             <a href = "/DBMS/Table.cpp">Table.cpp</a>           <a href = "/DBMS/Table.h">Table.h</a>             
<a href = "/DBMS/employees.txt">employees.txt</a>       <a href = "/DBMS/file.txt">file.txt</a>            <a href = "/DBMS/readme.md">readme.md</a>           <a href = "/DBMS/tempreadme.md">tempreadme.md</a></pre>         

A simple dbms which accepts SQL to
1. Create table 
    CREATE table table_name
2. Save table to file
3. Get **data type** of the information from the user at run time.
    * int
    * double
    * char
    * string
    all the above types are supported         
List of SQL Operations supported
1. SELECT : user can select which fields of information from the table to be displayed        
    ` SELECT *` // * implies all coloumns.
    * SELECT col1, col2
2. FROM : It handles the table from which information needs to be provided
    * FROM table_name
3. WHERE : It helps to filter specific records from the table
    * **relational operators supported**
    * = equal to, returns records with the value equal to provided
    * != not equal to, returns records with the value not equal to provide
    * < lesser than, returns records with the value lesser than provided 
    * \> greater than, returns records with the value greater than provided   
    * <= lesser than, returns records with the value lesser than or equal to provided
    * \>= greater than, returns records with the value greater than or equal to provided
    * **logical operators supported**
    * AND, returns the records which satisfies both the constraints 
    * OR, returns the records which satisfies either or the other constraints
    * NOT, returns the records which didn't satisfy the constraint
    all the above operators and operations are supported.
    * WHERE col1 \<relational operator> val
    * WHERE \<logical operator> col1 \<relational operator> col2       
    `WHERE NOT age >= 45 AND gender = f OR city = chennai`
4. ORDER_BY : sorts the list in ascending order by default.
    * DESC, sorts the list in descending order        
    ` ORDER_BY emp_id`         
     `ORDER_BY emp_id DESC ` 
        
    ```SQL
    ex : 
        SELECT * 
        FROM employees
        WHERE join_yr < 2012 AND NOT gender = f OR city = chennai
        ORDER_BY emp_id DESC
    ```
5. HELP : 
   * HELP ALL : lists all suported commands
   * HELP <command> : displays information about the specified command     
6. OPEN : OPEN <file_name> , loads Table from the file.   
7. ADD : adds records to the Table.
8. DELETE : delets a record from the Table     

</details>       



