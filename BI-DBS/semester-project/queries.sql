
set pagesize 1000
set echo on
set markup html on spool on head "<title>BI-DBS - Josef Doležal(dolezjo3) - Výstup SQL příkazů </title> <style type ='text/css'><!--body {background: #ffffc6} --></style>" body "<h2>BI-DBS - středa 16:15, lichý týden, paralelka 1 - Josef Doležal - Výstup SQL příkazů</h2>"
spool queries-log.html

       	
          --KOD DOTAZU: d1
 -- Zakázky, které se realizovaly na platformě Oracle.

SELECT DISTINCT p.NAME FROM PROJECT p
JOIN CONTRACT c ON( p.CONTRACT_ID = c.CONTRACT_ID )
JOIN USED_TECHNOLOGIES u ON( c.CONTRACT_ID = u.CONTRACT_ID )
JOIN TECHNOLOGY t ON( u.TECHNOLOGY_ID = t.TECHNOLOGY_ID )
WHERE t.LABEL LIKE '%Oracle%';
 

          --KOD DOTAZU: d2
 -- Vyber seznam zaměstnanců, kteří do systému nepřidali ani jednu zakázku od firmy HP.

SELECT EMPLOYEE_ID, PERSONAL_NUMBER FROM EMPLOYEE
MINUS
SELECT e.EMPLOYEE_ID, e.PERSONAL_NUMBER FROM EMPLOYEE e
JOIN CONTRACT c ON ( e.EMPLOYEE_ID = c.EMPLOYEE_ID )
JOIN COMPANY y ON ( c.COMPANY_ID = y.COMPANY_ID )
WHERE y.NAME = 'HP';
 

          --KOD DOTAZU: d3
 -- Vytvoření pohledu nad zaměstnanci, u kterých bude vidět celé jméno a osobní číslo.

CREATE OR REPLACE VIEW EMPLOYEE_INFO AS
SELECT EMPLOYEE.PERSONAL_NUMBER, PERSON.FIRST_NAME, PERSON.LAST_NAME
FROM EMPLOYEE JOIN PERSON USING (EMPLOYEE_ID);
 

          --KOD DOTAZU: d4
 -- Vyber jméno zaměstnance, jeho iniciály a počet kolizí iniciálů s jeho kolegy.

SELECT p.FIRST_NAME, p.LAST_NAME, SUBSTR( FIRST_NAME, 1, 1 ) || SUBSTR( LAST_NAME, 1, 1 ) INC, (
  SELECT COUNT( SUBSTR( FIRST_NAME, 1, 1 ) || SUBSTR( LAST_NAME, 1, 1 ) ) FROM PERSON n
  WHERE n.CONTACT_PERSON_ID IS NULL
  AND p.PERSON_ID != n.PERSON_ID
  AND SUBSTR( n.FIRST_NAME, 1, 1 ) || SUBSTR( n.LAST_NAME, 1, 1 ) = 
      SUBSTR( p.FIRST_NAME, 1, 1 ) || SUBSTR( p.LAST_NAME, 1, 1 ) ) INC_COUNT
FROM PERSON p
WHERE p.CONTACT_PERSON_ID IS NULL;
 

          --KOD DOTAZU: d5
 -- Seznam technologií použitých na zakázkách firmy Foxconn.

SELECT DISTINCT c.LABEL FROM TECHNOLOGY c
JOIN USED_TECHNOLOGIES u USING ( TECHNOLOGY_ID )
JOIN CONTRACT c ON ( u.CONTRACT_ID = c.CONTRACT_ID )
JOIN COMPANY y ON ( c.COMPANY_ID = y.COMPANY_ID )
WHERE y.NAME = 'Foxconn';
 

          --KOD DOTAZU: d6
 -- Finanční kategorie, která obsahuje nejvíce zakázek.

SELECT * FROM FINANCIAL_CATEGORY
WHERE FINANCIAL_CATEGORY_ID = (
  SELECT category FROM (
    SELECT FINANCIAL_CATEGORY_ID category, COUNT( CONTRACT_ID ) c
    FROM CONTRACT
    GROUP BY FINANCIAL_CATEGORY_ID
    ORDER BY c DESC )
  WHERE ROWNUM = 1
);
 

          --KOD DOTAZU: d8
 -- Zaměstnanci (jméno, příjmení a ID), kteří přidali nejvíce zakázek.

SELECT EMPLOYEE_ID, PERSON.FIRST_NAME, PERSON.LAST_NAME FROM (
  SELECT co.EMPLOYEE_ID, COUNT( co.EMPLOYEE_ID ) empl FROM CONTRACT co
  JOIN PROJECT pr ON( co.CONTRACT_ID = pr.CONTRACT_ID )
  GROUP BY co.EMPLOYEE_ID )
JOIN PERSON USING( EMPLOYEE_ID )
WHERE empl = ( SELECT MAX( cu ) mx FROM (
  SELECT c.EMPLOYEE_ID, COUNT( c.EMPLOYEE_ID ) cu FROM CONTRACT c
  JOIN PROJECT p ON( c.CONTRACT_ID = p.CONTRACT_ID )
  GROUP BY c.EMPLOYEE_ID )
) ORDER BY PERSON.LAST_NAME ASC;
 

          --KOD DOTAZU: d9
 -- Průměrný počet zakázek v každé finanční kategorii.

SELECT AVG( c ) FROM (
  SELECT FINANCIAL_CATEGORY_ID, COUNT( FINANCIAL_CATEGORY_ID ) c
  FROM CONTRACT
  GROUP BY FINANCIAL_CATEGORY_ID
);
 

          --KOD DOTAZU: d10
 -- Zaměstnanci, kteří pracojí nebo pracovali pouze na jednom projektu.

SELECT i.* FROM EMPLOYEE_INFO i
JOIN EMPLOYEE e ON ( i.PERSONAL_NUMBER = e.PERSONAL_NUMBER )
WHERE e.EMPLOYEE_ID IN (
  SELECT EMPLOYEE_ID FROM PROJECT_REALIZATION
  GROUP BY EMPLOYEE_ID
  HAVING( COUNT( CONTRACT_ID) = 1 )
);
 

          --KOD DOTAZU: d11
 -- ID zaměstnanců, kteří vložili zakázky ve všech finančních kategoriích.

SELECT EMPLOYEE_ID FROM EMPLOYEE
MINUS
SELECT EMPLOYEE_ID FROM (
  SELECT e.EMPLOYEE_ID, f.FINANCIAL_CATEGORY_ID
  FROM EMPLOYEE e
  CROSS JOIN FINANCIAL_CATEGORY f
  MINUS
  SELECT e.EMPLOYEE_ID, c.FINANCIAL_CATEGORY_ID
  FROM EMPLOYEE e
  JOIN CONTRACT c ON ( e.EMPLOYEE_ID = c.EMPLOYEE_ID )
);
 

          --KOD DOTAZU: d12
 -- Seznam finančních kategorií, které nebyly zaměstnancem s ID 1070 přidány k žádné zakázce.

SELECT * FROM FINANCIAL_CATEGORY
WHERE FINANCIAL_CATEGORY_ID NOT IN (
  SELECT DISTINCT FINANCIAL_CATEGORY_ID FROM CONTRACT
  WHERE EMPLOYEE_ID = 1070
);
 

          --KOD DOTAZU: d13
 -- Seznam zakázek, u kterých byly náklady vyšší než 20 000 000 nebo u nich byla využita technologie C++.

SELECT c.CONTRACT_ID, c.NAME FROM CONTRACT c
JOIN PROJECT p ON( c.CONTRACT_ID = p.CONTRACT_ID )
WHERE p.COST > 20000000
UNION
SELECT c.CONTRACT_ID, c.NAME FROM CONTRACT c
JOIN USED_TECHNOLOGIES u ON ( c.CONTRACT_ID = u.CONTRACT_ID )
JOIN TECHNOLOGY t ON( u.TECHNOLOGY_ID = t.TECHNOLOGY_ID )
WHERE t.LABEL = 'C++';
 

          --KOD DOTAZU: d14
 -- ID zakázek, na kterých pracují aspoň 4 zaměstnanci. Dotaz zobrazí i jejich přesný počet.

SELECT * FROM (
  SELECT CONTRACT_ID, COUNT( EMPLOYEE_ID ) EMPLOYEES FROM PROJECT_REALIZATION
  GROUP BY CONTRACT_ID
  ORDER BY EMPLOYEES DESC )
WHERE EMPLOYEES > 4;
 

          --KOD DOTAZU: d15
 -- Název, ID a název společnosti projektů, které byly započaty v roce 2015 a v tom samém roce byly také ukončeny.

SELECT p.NAME, p.CONTRACT_ID, m.NAME FROM PROJECT p
JOIN CONTRACT c ON ( p.CONTRACT_ID = c.CONTRACT_ID )
JOIN COMPANY m ON ( c.COMPANY_ID = m.COMPANY_ID )
WHERE EXTRACT( YEAR FROM p.START_DATE ) = '2015'
AND EXTRACT( YEAR FROM p.END_DATE ) = EXTRACT( YEAR FROM p.START_DATE );
 

          --KOD DOTAZU: d16
 -- Zakázkám, které nebyly tento rok ještě dokončeny zvyš náklady o 10%.

UPDATE PROJECT
SET COST = COST * 1.10
WHERE END_DATE IS NULL
AND EXTRACT( YEAR FROM START_DATE ) = (
  SELECT EXTRACT( YEAR FROM ADD_MONTHS( SYSDATE, -12)) FROM DUAL );
COMMIT;
 

          --KOD DOTAZU: d17
 -- Seznam zaměstnanců, kteří do dnes pracovali maximálně na jedné zakázce.

SELECT r.EMPLOYEE_ID 
FROM PROJECT_REALIZATION r
JOIN PROJECT p ON( r.CONTRACT_ID = p.CONTRACT_ID )
GROUP BY r.EMPLOYEE_ID
HAVING COUNT( r.CONTRACT_ID ) < 2
ORDER BY r.EMPLOYEE_ID;
 

          --KOD DOTAZU: d18
 -- Zakázky z finanční kategorie s ID 1000 (Do 1 milionu Kč) a zaměstnance, kteří je přidali včetně těch, kteří ji přidat mohli.

SELECT pr.CONTRACT_ID, pr.NAME, e.EMPLOYEE_ID FROM (
  SELECT p.* FROM PROJECT p
  JOIN CONTRACT c ON ( p.CONTRACT_ID = c.CONTRACT_ID )
  WHERE c.FINANCIAL_CATEGORY_ID = 1000 ) pr
RIGHT JOIN EMPLOYEE e ON ( pr.EMPLOYEE_ID = e.EMPLOYEE_ID )
WHERE e.EMPLOYEE_ID < 1030; -- podminka omezujici velikost vystupu
 

          --KOD DOTAZU: d19
 -- Zaměstnanci, kteří přidali zakázku s ID 1230 a 1290.

SELECT * FROM EMPLOYEE
WHERE EMPLOYEE_ID IN (
  SELECT EMPLOYEE_ID FROM PROJECT_REALIZATION
  WHERE CONTRACT_ID = 1230
  INTERSECT
  SELECT EMPLOYEE_ID FROM PROJECT_REALIZATION
  WHERE CONTRACT_ID = 1290 );
 

          --KOD DOTAZU: d20
 -- Technologie, které nebyly nasazeny u žádného klineta.

-- ALTERNATIVA 1
SELECT t.TECHNOLOGY_ID FROM TECHNOLOGY t
WHERE NOT EXISTS (
  SELECT * FROM USED_TECHNOLOGIES u
  WHERE u.TECHNOLOGY_ID = t.TECHNOLOGY_ID
)
AND t.TECHNOLOGY_ID < 1050; -- omezeujici podminka pro velikost vystupu
-- ALTERNATIVA 2
SELECT TECHNOLOGY_ID FROM TECHNOLOGY
WHERE TECHNOLOGY_ID < 1050 -- omezujici podminka pro velikost vystupu
MINUS
SELECT TECHNOLOGY_ID FROM USED_TECHNOLOGIES
WHERE TECHNOLOGY_ID < 1050; -- omezujici podminka pro velikost vystupu
-- ALTERNATIVA 3
SELECT TECHNOLOGY_ID FROM TECHNOLOGY
WHERE TECHNOLOGY_ID NOT IN (
  SELECT TECHNOLOGY_ID FROM USED_TECHNOLOGIES
)
AND TECHNOLOGY_ID < 1050; -- omezujici podminka pro velikost vystupu
 

          --KOD DOTAZU: d21
 -- Zákazníci, s kterými byla uzavřena zakázka v roce 2014.

ALTER SESSION SET NLS_DATE_FORMAT='mm-dd-yyyy';
SELECT c.CONTRACT_ID, p.NAME FROM PROJECT p
JOIN CONTRACT c ON( p.CONTRACT_ID = c.CONTRACT_ID )
WHERE c.DATE_ADDED BETWEEN TO_DATE( '01-01-2014' ) AND TO_DATE( '12-31-2014' );
 

          --KOD DOTAZU: d22
 -- Jména společností a jejich adresy.

SELECT c.NAME, a.STATE, a.CITY, a.STREET_ADDRESS_LINE1, a.POSTAL_CODE
FROM COMPANY c
FULL JOIN ADDRESS a ON( c.COMPANY_ID = a.COMPANY_ID );
 

          --KOD DOTAZU: d23
 -- K zakázce s ID 1230 přiřaď zaměstnance, kteří na ní ještě nepracují.

INSERT INTO PROJECT_REALIZATION ( EMPLOYEE_ID, CONTRACT_ID, NAME )
SELECT u.EMPLOYEE_ID, c.CONTRACT_ID, TRIM( c.NAME ) FROM (
  SELECT EMPLOYEE_ID FROM EMPLOYEE
  MINUS
  SELECT EMPLOYEE_ID FROM PROJECT_REALIZATION
  WHERE PROJECT_REALIZATION.CONTRACT_ID = 1230
) u
JOIN CONTRACT c ON ( 1 = 1 )
WHERE c.CONTRACT_ID = 1230;
COMMIT;
 

          --KOD DOTAZU: d24
 -- Smaž všechny zákazníky (a jejich kontaktní osoby), se kterými nebyla prozatím uzavřena žádná zakázka.

DELETE FROM COMPANY WHERE COMPANY_ID IN (
  SELECT COMPANY_ID FROM COMPANY
  MINUS
  SELECT DISTINCT COMPANY_ID FROM CONTRACT
  JOIN PROJECT USING( CONTRACT_ID )
  );
COMMIT;
 

          --KOD DOTAZU: d7
 -- Kontakty na osoby, které jsou spojené se zakázkou 1220 nebo 1310.

SELECT p.FIRST_NAME, P.LAST_NAME, p.EMAIL, p.PHONE, cp.JOB_TITLE
FROM CONTACT_PERSON cp
JOIN PERSON p ON( cp.CONTACT_PERSON_ID = p.CONTACT_PERSON_ID )
JOIN COMPANY c ON ( cp.COMPANY_ID = c.COMPANY_ID )
JOIN CONTRACT ct ON ( c.COMPANY_ID = ct.COMPANY_ID )
WHERE ct.CONTRACT_ID IN ( 1220, 1310 );
 

          --KOD DOTAZU: d25
 -- Projekty, které má na starosti Paul Cohen (ID 1040) předeleguj na Johna Frye.

UPDATE PROJECT SET EMPLOYEE_ID = (
  SELECT e.EMPLOYEE_ID FROM EMPLOYEE e
  JOIN PERSON p ON ( e.EMPLOYEE_ID = p.PERSON_ID )
  WHERE p.FIRST_NAME = 'John'
  AND p.LAST_NAME = 'Frye'
) WHERE EMPLOYEE_ID = 1040;
COMMIT;
 

set markup html off
spool off
