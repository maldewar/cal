//Name: Add body (circle)
//Tags: body, circle
//Add a body with a circle fixture at the cursor position

body b = addBody(-1, '{"name":"gravitron","type":"dynamic","awake":true}');
uint numSides = 6;
float radius = 0.075;
string xValues;
string yValues;
for (uint n = 0; n < numSides; n++) {
  float angle = n * (dr(360) / numSides);
  if ( n > 0 ) {
    xValues += ',';
    yValues += ',';
  }
  vec2 v;
  v.set( radius * cos(angle), radius * sin(angle) );
  xValues += v.x;
  yValues += v.y;
}
string fixtureDef = '{"name":"body_fixture","density":15,"shapes":[{"radius":0,"type":"polygon"}],"friction":1,"filter-categoryBits":2,"filter-maskBits":1,"vertices":{"x":['+xValues+'],"y":['+yValues+']}}';
b.addFixture(-1, fixtureDef);
b.addFixture(-1, '{"name":"body_sensor","density":1,"sensor":true,"restitution":0.4,"friction":1,"shapes":[{"radius":0.3,"type":"circle"}],"friction":0.2,"vertices":{"x":[0],"y":[0]}}');
b.setCustomString("category", "gravitron");
b.setCustomBool("active", true);
b.setPos( cursor() );

