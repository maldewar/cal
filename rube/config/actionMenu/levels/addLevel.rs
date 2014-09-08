//Name: Add Exit
//Tags: calaveras, exit
//Add an exit object with a sensor.

body b = addBody(-1, '{"name":"level","type":"static"}');
b.addFixture(-1, '{"name":"body_sensor","sensor":true,"shapes":[{"radius":0.2,"type":"circle"}],"vertices":{"x":[0],"y":[0]}}');
b.setCustomString("category", "level");
b.setCustomInt("level", 0);
b.setCustomString("armature", "");
b.setCustomString("title", "");
b.setPos( cursor() );

