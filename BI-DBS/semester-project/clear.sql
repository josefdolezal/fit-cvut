select 'drop table ' || table_name || ' cascade constraints purge;' from user_tables;
select 'drop sequence ' || sequence_name || ';' from user_sequences;
select 'drop trigger ' || trigger_name || ';' from user_triggers;

drop table ADDRESS cascade constraints purge;
drop table COMPANY cascade constraints purge;
drop table CONTACT_PERSON cascade constraints purge;
drop table CONTRACT cascade constraints purge;
drop table EMPLOYEE cascade constraints purge;
drop table FINANCIAL_CATEGORY cascade constraints purge;
drop table PERSON cascade constraints purge;
drop table PROJECT cascade constraints purge;
drop table PROJECT_REALIZATION cascade constraints purge;
drop table TECHNOLOGY cascade constraints purge;
drop table USED_TECHNOLOGIES cascade constraints purge;

drop sequence ADDRESSES_SEQUENCE;
drop sequence COMPANIES_SEQUENCE;
drop sequence CONTRACTS_SEQUENCE;
drop sequence FIN_CATEGORIES_SEQUENCE;
drop sequence PERSONS_SEQUENCE;
drop sequence TECHNOLOGIES_SEQUENCE;
drop sequence CONT_PERS_SEQUENCE;
drop sequence EMPLOYEES_SEQUENCE;

drop trigger PRSN_SEQ_TRIGGER;
drop trigger TECH_SEQ_TRIGGER;
drop trigger FCAT_SEQ_TRIGGER;
drop trigger CONT_SEQ_TRIGGER;
drop trigger ADDR_SEQ_TRIGGER;
drop trigger COMP_SEQ_TRIGGER;
drop trigger ARC_FKARC_1_EMPLOYEE;
drop trigger ARC_FKARC_1_CONTACT_PERSON;
