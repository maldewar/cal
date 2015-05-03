#include "Entity.h"

std::unordered_map<int, int> Entity::m_ids;

Entity::Entity() {
  m_id = "";
  m_worldLayer = nullptr;
  m_body = nullptr;
  m_width = 0;
  m_height = 0;
  m_skeletonNode = nullptr;
  m_animation = 0;
  m_skin = 0;
  m_shapeDrawEnabled = false;
  m_color = cocos2d::Color4F(0.1, 0.1, 0.1, 1);
  m_zOrderDraw = 0;
  m_zOrderTouch = 0;
  setAutoId();
}

Entity::~Entity() {
}

void Entity::setId(std::string id) {
  m_id = id;
}

std::string Entity::getId() {
  return m_id;
}

int Entity::getType() {
  return 0;
}

void Entity::setBody(b2Body* body) {
  m_body = body;
  m_body->SetUserData(this);
}

b2Body* Entity::getBody() {
  return m_body;
}

void Entity::setWorldLevelLayer(WorldLevelLayer* worldLevelLayer) {
  m_worldLayer = worldLevelLayer;
}

WorldLevelLayer* Entity::getWorldLevelLayer() {
  return m_worldLayer;
}

void Entity::update(float dt)
{
  Node::update(dt);
  if ( m_body ) {
    cocos2d::Vec2 position = cocos2d::Vec2(0,0);
    position.x = m_body->GetPosition().x;
    position.y = m_body->GetPosition().y;
    setRotation(CC_RADIANS_TO_DEGREES(-m_body->GetAngle()));
    setPosition(position);
  }
}

void Entity::select() {
}

void Entity::select(b2Body* body) {
}

void Entity::select(cocos2d::Touch* touch) {
}

float Entity::getSkeletonScale() {
  return PX_TO_M/2;
}

float Entity::getGroundOffset() {
  return DESIGN_HEIGHT * m_height * -0.5;
}

void Entity::enableShapeDraw(bool isShapeDrawEnabled) {
  m_shapeDrawEnabled = isShapeDrawEnabled;
}

void Entity::setZOrderDraw(int zOrderDraw) {
  m_zOrderDraw = zOrderDraw;
}

int Entity::getZOrderDraw() {
  return m_zOrderDraw;
}

void Entity::setZOrderTouch(int zOrderTouch) {
  m_zOrderTouch = zOrderTouch;
}

int Entity::getZOrderTouch() {
  return m_zOrderTouch;
}

void Entity::setAutoId() {
  int type = getType();
  if (m_ids.count(type) == 0) {
    m_ids[type] = 0;
  }
  std::string kind;
  switch(type) {
    case ENTITY_TYPE_UNIT:
      kind = "unit_";
      break;
    case ENTITY_TYPE_ENTRY:
      kind = "entry_";
      break;
    case ENTITY_TYPE_AREA:
      kind = "area_";
      break;
    case ENTITY_TYPE_EXIT:
      kind = "exit_";
      break;
    case ENTITY_TYPE_GRAVITRON:
      kind = "gravitron_";
      break;
    case ENTITY_TYPE_IMAGE:
      kind = "image_";
      break;
    case ENTITY_TYPE_IMAGE_BODY:
      kind = "image_body_";
      break;
    case ENTITY_TYPE_LEVEL:
      kind = "level_";
      break;
    case ENTITY_TYPE_BRANCH:
      kind = "branch_";
      break;
    case ENTITY_TYPE_DRAGGABLE:
      kind = "draggable_";
      break;
    default:
      kind = "undefined_";
  }
  m_id = kind + std::to_string(m_ids[type]);
  m_ids[type]++;
}

void Entity::onDirectionChange(int direction) {
  if (direction > 0) {
    m_skeletonNode->setScaleX(1);
  } else if (direction < 0) {
    m_skeletonNode->setScaleX(-1);
  }
}

void Entity::setAnimation(int animation) {
  m_animation = animation;
}

void Entity::setSkin(int skin) {
  m_skin = skin;
}

int Entity::getSkin() {
  return m_skin;
}

void Entity::randomSkin() {
}

bool Entity::onStartTouchEvent(cocos2d::Touch* touch) {
  return false;
}

bool Entity::onMoveTouchEvent(cocos2d::Touch* touch) {
  return false;
}

bool Entity::onEndTouchEvent(cocos2d::Touch* touch) {
  return false;
}

void Entity::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, uint32_t flags) {
  if (m_shapeDrawEnabled) {
    m_customCommand.init(_globalZOrder);
    m_customCommand.func = CC_CALLBACK_0(Entity::onDraw, this, transform, flags);
    renderer->addCommand(&m_customCommand);
  }
}

void Entity::onDraw(const cocos2d::Mat4 &transform, uint32_t flags) {
  cocos2d::Director::getInstance()->pushMatrix(cocos2d::MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
  cocos2d::Director::getInstance()->loadMatrix(cocos2d::MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
  
  float mRatio = 1.0f;
  int maxVertices = 64;              
  cocos2d::Point *mVertices = new cocos2d::Point[maxVertices];
  b2PolygonShape* poly = nullptr;
  int32 vertexCount = 0;
  const b2Transform& _xf = m_body->GetTransform();
  for (b2Fixture* f = m_body->GetFixtureList(); f; f = f->GetNext()) {
    poly = (b2PolygonShape*)f->GetShape();
    vertexCount = poly->m_count;
    b2Assert(vertexCount <= b2_maxPolygonVertices);
    b2Vec2 vertices[b2_maxPolygonVertices];
    for (int32 i = 0; i < vertexCount; ++i)
    {
      vertices[i] = poly->m_vertices[i];
    }
    for (int i = 0; i < maxVertices && i < vertexCount; i++ ) {
      mVertices[i].setPoint( mRatio * vertices[i].x, mRatio * vertices[i].y );
    }
    cocos2d::DrawPrimitives::drawSolidPoly(mVertices, vertexCount, m_color);
    cocos2d::DrawPrimitives::setDrawColor4F(m_color.r, m_color.g, m_color.b, m_color.a);
    cocos2d::DrawPrimitives::drawPoly(mVertices, vertexCount, true);
  }
  cocos2d::Director::getInstance()->popMatrix(cocos2d::MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}
