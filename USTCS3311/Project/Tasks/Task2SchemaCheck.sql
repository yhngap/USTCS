/* COMP 3311: Task 2 - Final Year Project Management System: Schema Check */


/*                                ***** IMPORTANT NOTES *****
   If each tuple in this script file can be successfully inserted into its respective table, 
   then the table has been defined correctly as to the number of the attributes and possibly 
   the order and type of each attribute. However, the order and type of the attributes is 
   not guaranteed to be correct even if a tuple can be inserted successfully! Furthermore, 
   the tuples need to be inserted in the correct order and the order in which they appear 
   in this script file is not necessarily the correct order in which the tables should be 
   created. The tuples may need to be reordered according to the specified referential 
   integrity constraints so that they can be successfully inserted into the tables. */

/********** CSEStudent relation **********/
insert into CSEStudent values ('studentusername','Test Student',99);

/********** Faculty relation **********/
insert into Faculty values ('facultyusername','Faculty Name','0000','FN');

/********** FYP relation **********/
insert into FYP values (99,'Test title','Test description','Database','project','Test skill',1,1,'Y');

/********** FYPCategory relation  **********/
insert into FYPCategory values ('Database');

/********** InterestedIn relation **********/
insert into InterestedIn values (99,99,1);

/********** ProjectGroup relation **********/
insert into ProjectGroup values (99,'FN1',99,null);

/********** RequirementGrades relation **********/
insert into RequirementGrades values ('facultyusername','studentusername',50,50,50,50);

/********** Supervises relation **********/
insert into Supervises values ('facultyusername',99);