//Name: Add body (circle)
//Tags: body, circle

//Add a body with a circle fixture at the cursor position

body b = addBody(-1, '{"name":"unit","type":"dynamic","awake":true}');
b.addFixture(-1, '{"density":1,"restitution":0.4,"friction":1,"filter-categoryBits":2,"filter-maskBits":1,"shapes":[{"name":"unit","radius":0.15,"type":"circle"}],"friction":0.8,"vertices":{"x":[0],"y":[0]}}');
b.setCustomString("category", "unit");
b.setPos( cursor() );

