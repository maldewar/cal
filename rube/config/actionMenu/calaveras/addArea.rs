//Name: Add body (polygon)
//Tags: body, polygon
//Add body with a polygon fixture with the number of sides specified by the user at the cursor position

uint numSides = 3;
body b = addBody(-1, '{"name":"area","type":"static","awake":true}');
float radius = 0.6;	
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
string fixtureDef = '{"density":1,"shapes":[{"radius":0,"type":"polygon"}],"friction":0.8,"vertices":{"x":['+xValues+'],"y":['+yValues+']}}';
b.addFixture(-1, fixtureDef);
b.setCustomString("category", "area");
b.setCustomString("material", "default");
b.setCustomInt("zOrderTouch", 0);
b.setCustomInt("zOrderDraw", 500);
b.setPos( cursor() );

