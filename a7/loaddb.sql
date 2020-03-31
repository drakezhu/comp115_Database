drop table if exists R;
drop table if exists S;
drop table if exists T;
drop table if exists U;

create table U(u_id int not null primary key, 
               u_5 int, 
               u_filler varchar);

create table T(t_id int not null primary key, 
               t_5 int,     
               t_filler varchar);

create table S(s_id int not null primary key, 
               s_4 int, 
               s_20 int, 
               s_filler varchar, 
               t_id int references T, 
               u_id int references U);

create table R(r_id int not null primary key, 
               r_2 int, 
               r_10 int, 
               r_1p int, 
               r_10p int, 
               r_50p int, 
               r_filler varchar, 
               s_id int references S);

\copy u from 'u.csv' with delimiter ',' csv;
\copy t from 't.csv' with delimiter ',' csv;
\copy s from 's.csv' with delimiter ',' csv;
\copy r from 'r.csv' with delimiter ',' csv;


