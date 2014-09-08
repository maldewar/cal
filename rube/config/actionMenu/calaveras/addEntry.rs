//Name: Add body
//Tags: body

//add a body with no name at the current cursor position

body entry = addBody(-1, '{"name":"entry","type":"static","awake":true}');
entry.setCustomString("category", "entry");
entry.setCustomInt("capacity", -1);
entry.setCustomInt("interval", 100);
entry.setCustomBool("isOpen", false);
entry.setCustomBool("useOpenTimer", true);
entry.setCustomInt("openTimer", 1000);
entry.setCustomFloat("forceMinDistance", 0);
entry.setCustomFloat("forceMaxDistance", 0);
entry.setCustomFloat("forceMaxAngle", 0);
entry.setCustomFloat("forceMinAngularImpulse", 0);
entry.setCustomFloat("forceMaxAngularImpulse", 0);
entry.setPos(cursor());
