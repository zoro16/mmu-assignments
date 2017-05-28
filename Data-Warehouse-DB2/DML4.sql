--ALTER TABLE MANUFACTURER DROP COLUMN MANU_NAME; 
--ALTER TABLE MANUFACTURER DROP COLUMN MANU_COUNTRY;

--ALTER TABLE MANUFACTURER ADD COLUMN MANU_NAME VARCHAR(13);
--ALTER TABLE MANUFACTURER ADD COLUMN MANU_COUNTRY VARCHAR(13);

--DELETE FROM MANUFACTURER;

------------------------------------------------------------------------
SELECT * FROM SALES;
SELECT * FROM MANUFACTURER;
SELECT * FROM BRANCH;
SELECT * FROM CAR;
SELECT * FROM CUSTOMER;
SELECT * FROM TIME;

------------------------------------------------------------------------
-- I'm assuming DB2 won't allow you to provide a guide for the data 
-- conversion but I pray to the SQL Server gods.Given that assumption, 
-- add a new column, migrate the data over, verify your work, drop the 
-- original column, rename the new.

--1)
ALTER TABLE CUSTOMER ADD col1_new decimal(11,2) NULL;

--2)
UPDATE CUSTOMER SET col1_new = CAST(CU_IncomePerYear  AS decimal(11,2));

--3)
ALTER TABLE CUSTOMER DROP COLUMN CU_IncomePerYear;

--4)
ALTER TABLE CUSTOMER RENAME COLUMN col1_new TO CU_IncomePerYear ;

--5)
ALTER TABLE CUSTOMER ADD CU_CURR CHAR(3) WITH DEFAULT 'USD' ;
