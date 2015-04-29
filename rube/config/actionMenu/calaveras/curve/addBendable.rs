//Name: Add Bendable Curve
//Tags: body, polygon
//Add body with a polygon fixture with the number of sides specified by the user at the cursor position

uint numSegments = queryNumericValue('Number of segments', 4);
float fLength = queryNumericValue('Length', 3);
float fAngle = queryNumericValue('Reference Angle (Degrees)', 0);
fAngle = fAngle * 0.017453289;
float fTopAngle = queryNumericValue('Top Angle (Degrees)', 7);
fTopAngle = fTopAngle * 0.017453289;
float fBottomAngle = queryNumericValue('Bottom Angle (Degrees)', 0);
fBottomAngle = fBottomAngle * -0.017453289;
float fInitialHeight = queryNumericValue('Initial Segment Height', 0.5);
float fFinalHeight = queryNumericValue('Final Segment Height', fInitialHeight);
float fInitialDensity = queryNumericValue('Initial Segment Density', 1);
float fFinalDensity = queryNumericValue('Final Segment Density', 0.4);
bool bIsPositionable = queryYesNo('Is Positionable?');
float fMotorSpeed = 0;
if (bIsPositionable) {
  fMotorSpeed = queryNumericValue('Motor Speed (degrees/sec)', 30);
  fMotorSpeed = fMotorSpeed * 0.017453289;
}
bool bIsDraggable = queryYesNo('Is Draggable?');
float fTopM, fBottomM;
float fAx, fBx, fCx, fDx;
float fAy, fBy, fCy, fDy;
float fSegmentLength, fSegmentExtra, fDensityStep;
vec2 anchorA = cursor();
vec2 anchorB = cursor();
body bodyA;
string m_id;

fSegmentLength = fLength/numSegments;
fDensityStep = (fInitialDensity - fFinalDensity)/numSegments;
fTopM = (fFinalHeight/2 - fInitialHeight/2) / fLength;
fBottomM = -fTopM;

for (uint n = 0; n < numSegments; n++) {

  if (n < numSegments - 1)
    fSegmentExtra = fSegmentLength/15;
  else
    fSegmentExtra = 0;

  fAx = n * fSegmentLength;
  fAy = fAx * fTopM + fInitialHeight/2;
  fAx -= fSegmentLength/2 + n*fSegmentLength;

  fBx = (n +1) * fSegmentLength + fSegmentExtra;
  fBy = fBx * fTopM + fInitialHeight/2;
  fBx -= fSegmentLength/2 + n*fSegmentLength;

  fCx = n * fSegmentLength;
  fCy = -fAy;
  fCx -= fSegmentLength/2 + n*fSegmentLength;

  fDx = (n + 1) * fSegmentLength + fSegmentExtra;
  fDy = -fBy;
  fDx -= fSegmentLength/2 + n*fSegmentLength;

  body b = addBody(-1, '{"type":"dynamic","awake":true}');

  string fixtureDef = '{"density":'+(fInitialDensity - (n*fDensityStep))+',"shapes":[{"radius":0,"type":"polygon"}],"friction":0.2,"vertices":{"x":['+fCx+','+fDx+','+fBx+','+fAx+'],"y":['+fCy+','+fDy+','+fBy+','+fAy+']}}';
  b.addFixture(-1, fixtureDef);

  vec2 pos = cursor();
  pos.x += n * fSegmentLength;
  b.setPos( pos );

  // Join
  anchorB.x = (-fSegmentLength/2) * 1;
  anchorB.y = 0;
  if ( n > 0) {
    joint j = addJoint(-1, '{"type":"revolute","enableLimit":true,"enableMotor":true,"upperLimit":'+fTopAngle+',"lowerLimit":'+fBottomAngle+',"bodyA":'+bodyA.id+',"bodyB":'+b.id+',"anchorA":{"x":'+anchorA.x+',"y":'+anchorA.y+'},"anchorB":{"x":'+anchorB.x+',"y":'+anchorB.y+'}}');
    j.setCustomString("category", "branch");
    j.setCustomString("m_id", 'branch_' + m_id);
    if (bIsDraggable && n == numSegments - 1) {
      b.addFixture(-1, '{"name":"draggable_sensor","density":0,"sensor":true,"restitution":0.4,"friction":1,"shapes":[{"radius":0.4,"type":"circle"}],"friction":0.2,"vertices":{"x":['+(fSegmentLength/2)+'],"y":['+0+']}}');
      b.setCustomString("category", "draggable");
      b.setCustomBool("active", true);
      b.setCustomFloat("draggablePinX", fSegmentLength/2);
      b.setCustomFloat("draggablePinY", 0);
    }
    b.setCustomString("belongsToCategory", "branch");
    b.setCustomString("belongsToId", "branch_" + m_id);
    b.setCustomInt("belongsToIndex", n - 1);
  } else {
    // Add base sensor
    vec2 sensorPosition = cursor();
    sensorPosition.y = 0;
    sensorPosition.x = 0;
    b.addFixture(-1, '{"name":"body_sensor","density":0,"sensor":true,"restitution":0.4,"friction":1,"shapes":[{"radius":0.4,"type":"circle"}],"friction":0.2,"vertices":{"x":['+sensorPosition.x+'],"y":['+sensorPosition.y+']}}');
    b.setCustomString("category", "branch");
    b.setCustomBool("active", true);
    b.setCustomBool("isPositionable", bIsPositionable);
    b.setCustomBool("isDraggable", bIsDraggable);
    b.setCustomFloat("angle", fAngle);
    b.setCustomFloat("topAngle", fTopAngle);
    b.setCustomFloat("bottomAngle", fBottomAngle);
    b.setCustomFloat("motorSpeed", fMotorSpeed);
    b.setCustomString("m_id", 'branch_' + b.id);
    b.setCustomInt("skin",0);
    m_id = b.id;
  }
  bodyA = b;
  anchorA.x = (fSegmentLength/2);
  anchorA.y = 0;
}
