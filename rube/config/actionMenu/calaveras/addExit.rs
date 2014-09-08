//Name: Add Exit
//Tags: calaveras, exit
//Add an exit object with a sensor.

body b = addBody(-1, '{"name":"exit","type":"static"}');
b.addFixture(-1, '{"name":"body_sensor","sensor":true,"shapes":[{"radius":0.3,"type":"circle"}],"vertices":{"x":[0],"y":[0]}}');
b.setCustomString("category", "exit");
b.setCustomInt("capacity", 0);
b.setCustomBool("isOpen", false);
b.setCustomBool("useOpenTimer", true);
b.setCustomInt("openTimer", 1000);
b.setPos( cursor() );

