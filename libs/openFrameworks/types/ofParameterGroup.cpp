#include "ofParameter.h"
#include "ofUtils.h"

ofParameterGroup::ofParameterGroup()
	: obj(new Value) {
}

void ofParameterGroup::add(ofAbstractParameter & parameter) {
	auto param = parameter.newReference();
	auto escaped_name = param->getEscapedName();
	if (contains(escaped_name)) {
		ofLogWarning() << "Adding another parameter with same name '" << param->getName() << "' to group '" << getName() << "'";
	}
	obj->parameters.push_back(param);
	obj->parametersIndex[escaped_name] = obj->parameters.size() - 1;
	param->setParent(*this);
}

void ofParameterGroup::remove(ofAbstractParameter & param) {
	for (auto & p : obj->parameters) {
		if (p->isReferenceTo(param)) {
			remove(param.getName());
			return;
		}
	}
}

void ofParameterGroup::remove(size_t index) {
	if (index > obj->parameters.size()) {
		return;
	}
	remove(obj->parameters[index]->getName());
}

void ofParameterGroup::remove(const std::string & name) {
	auto escaped_name = escape(name);
	if (!contains(escaped_name)) {
		ofLogVerbose("ofParameterGroup::remove") << "attempt at removing non-present name " << name;
		return;
	}
	size_t paramIndex = obj->parametersIndex[escaped_name];
	obj->parameters.erase(obj->parameters.begin() + paramIndex);
	obj->parametersIndex.erase(escaped_name);
	std::for_each(obj->parameters.begin() + paramIndex, obj->parameters.end(), [&](std::shared_ptr<ofAbstractParameter> & p) {
		obj->parametersIndex[p->getEscapedName()] -= 1;
	});
}

void ofParameterGroup::clear() {
	auto name = this->getName();
	obj.reset(new Value);
	setName(name);
}

std::string ofParameterGroup::valueType() const {
	return typeid(*this).name();
}

const ofParameter<void> & ofParameterGroup::getVoid(const std::string & name) const {
	return get<void>(name);
}

const ofParameter<bool> & ofParameterGroup::getBool(const std::string & name) const {
	return get<bool>(name);
}

const ofParameter<int> & ofParameterGroup::getInt(const std::string & name) const {
	return get<int>(name);
}

const ofParameter<float> & ofParameterGroup::getFloat(const std::string & name) const {
	return get<float>(name);
}

const ofParameter<char> & ofParameterGroup::getChar(const std::string & name) const {
	return get<char>(name);
}

const ofParameter<std::string> & ofParameterGroup::getString(const std::string & name) const {
	return get<std::string>(name);
}

const ofParameter<ofPoint> & ofParameterGroup::getPoint(const std::string & name) const {
	return get<ofPoint>(name);
}

const ofParameter<ofDefaultVec2> & ofParameterGroup::getVec2f(const std::string & name) const {
	return get<ofDefaultVec2>(name);
}

const ofParameter<ofDefaultVec3> & ofParameterGroup::getVec3f(const std::string & name) const {
	return get<ofDefaultVec3>(name);
}

const ofParameter<ofDefaultVec4> & ofParameterGroup::getVec4f(const std::string & name) const {
	return get<ofDefaultVec4>(name);
}

const ofParameter<ofColor> & ofParameterGroup::getColor(const std::string & name) const {
	return get<ofColor>(name);
}

const ofParameter<ofShortColor> & ofParameterGroup::getShortColor(const std::string & name) const {
	return get<ofShortColor>(name);
}

const ofParameter<ofFloatColor> & ofParameterGroup::getFloatColor(const std::string & name) const {
	return get<ofFloatColor>(name);
}

const ofParameter<ofRectangle> & ofParameterGroup::getRectangle(const std::string & name) const {
	return get<ofRectangle>(name);
}

const ofParameterGroup & ofParameterGroup::getGroup(const std::string & name) const {
	return static_cast<const ofParameterGroup &>(get(name));
}

const ofParameter<void> & ofParameterGroup::getVoid(std::size_t pos) const {
	return get<void>(pos);
}

const ofParameter<bool> & ofParameterGroup::getBool(std::size_t pos) const {
	return get<bool>(pos);
}

const ofParameter<int> & ofParameterGroup::getInt(std::size_t pos) const {
	return get<int>(pos);
}

const ofParameter<float> & ofParameterGroup::getFloat(std::size_t pos) const {
	return get<float>(pos);
}

const ofParameter<char> & ofParameterGroup::getChar(std::size_t pos) const {
	return get<char>(pos);
}

const ofParameter<std::string> & ofParameterGroup::getString(std::size_t pos) const {
	return get<std::string>(pos);
}

const ofParameter<ofPoint> & ofParameterGroup::getPoint(std::size_t pos) const {
	return get<ofPoint>(pos);
}

const ofParameter<ofDefaultVec2> & ofParameterGroup::getVec2f(std::size_t pos) const {
	return get<ofDefaultVec2>(pos);
}

const ofParameter<ofDefaultVec3> & ofParameterGroup::getVec3f(std::size_t pos) const {
	return get<ofDefaultVec3>(pos);
}

const ofParameter<ofDefaultVec4> & ofParameterGroup::getVec4f(std::size_t pos) const {
	return get<ofDefaultVec4>(pos);
}

const ofParameter<ofColor> & ofParameterGroup::getColor(std::size_t pos) const {
	return get<ofColor>(pos);
}

const ofParameter<ofShortColor> & ofParameterGroup::getShortColor(std::size_t pos) const {
	return get<ofShortColor>(pos);
}

const ofParameter<ofFloatColor> & ofParameterGroup::getFloatColor(std::size_t pos) const {
	return get<ofFloatColor>(pos);
}

const ofParameter<ofRectangle> & ofParameterGroup::getRectangle(std::size_t pos) const {
	return get<ofRectangle>(pos);
}

const ofParameterGroup & ofParameterGroup::getGroup(std::size_t pos) const {
	if (pos >= size()) {
		throw std::out_of_range(("get(): " + ofToString(pos) + "out of bounds").c_str());
	} else {
		if (getType(pos) == typeid(ofParameterGroup).name()) {
			return *static_cast<ofParameterGroup *>(obj->parameters[pos].get());
		} else {
			throw std::runtime_error(("get():  bad type for pos " + ofToString(pos) + ", returning empty group").c_str());
		}
	}
}

ofParameter<void> & ofParameterGroup::getVoid(const std::string & name) {
	return get<void>(name);
}

ofParameter<bool> & ofParameterGroup::getBool(const std::string & name) {
	return get<bool>(name);
}

ofParameter<int> & ofParameterGroup::getInt(const std::string & name) {
	return get<int>(name);
}

ofParameter<float> & ofParameterGroup::getFloat(const std::string & name) {
	return get<float>(name);
}

ofParameter<char> & ofParameterGroup::getChar(const std::string & name) {
	return get<char>(name);
}

ofParameter<std::string> & ofParameterGroup::getString(const std::string & name) {
	return get<std::string>(name);
}

ofParameter<ofPoint> & ofParameterGroup::getPoint(const std::string & name) {
	return get<ofPoint>(name);
}

ofParameter<ofDefaultVec2> & ofParameterGroup::getVec2f(const std::string & name) {
	return get<ofDefaultVec2>(name);
}

ofParameter<ofDefaultVec3> & ofParameterGroup::getVec3f(const std::string & name) {
	return get<ofDefaultVec3>(name);
}

ofParameter<ofDefaultVec4> & ofParameterGroup::getVec4f(const std::string & name) {
	return get<ofDefaultVec4>(name);
}

ofParameter<ofColor> & ofParameterGroup::getColor(const std::string & name) {
	return get<ofColor>(name);
}

ofParameter<ofShortColor> & ofParameterGroup::getShortColor(const std::string & name) {
	return get<ofShortColor>(name);
}

ofParameter<ofFloatColor> & ofParameterGroup::getFloatColor(const std::string & name) {
	return get<ofFloatColor>(name);
}
ofParameter<ofRectangle> & ofParameterGroup::getRectangle(const std::string & name) {
	return get<ofRectangle>(name);
}

ofParameterGroup & ofParameterGroup::getGroup(const std::string & name) {
	return static_cast<ofParameterGroup &>(get(name));
}

ofParameter<void> & ofParameterGroup::getVoid(std::size_t pos) {
	return get<void>(pos);
}

ofParameter<bool> & ofParameterGroup::getBool(std::size_t pos) {
	return get<bool>(pos);
}

ofParameter<int> & ofParameterGroup::getInt(std::size_t pos) {
	return get<int>(pos);
}

ofParameter<float> & ofParameterGroup::getFloat(std::size_t pos) {
	return get<float>(pos);
}

ofParameter<char> & ofParameterGroup::getChar(std::size_t pos) {
	return get<char>(pos);
}

ofParameter<std::string> & ofParameterGroup::getString(std::size_t pos) {
	return get<std::string>(pos);
}

ofParameter<ofPoint> & ofParameterGroup::getPoint(std::size_t pos) {
	return get<ofPoint>(pos);
}

ofParameter<ofDefaultVec2> & ofParameterGroup::getVec2f(std::size_t pos) {
	return get<ofDefaultVec2>(pos);
}

ofParameter<ofDefaultVec3> & ofParameterGroup::getVec3f(std::size_t pos) {
	return get<ofDefaultVec3>(pos);
}

ofParameter<ofDefaultVec4> & ofParameterGroup::getVec4f(std::size_t pos) {
	return get<ofDefaultVec4>(pos);
}

ofParameter<ofColor> & ofParameterGroup::getColor(std::size_t pos) {
	return get<ofColor>(pos);
}

ofParameter<ofShortColor> & ofParameterGroup::getShortColor(std::size_t pos) {
	return get<ofShortColor>(pos);
}

ofParameter<ofFloatColor> & ofParameterGroup::getFloatColor(std::size_t pos) {
	return get<ofFloatColor>(pos);
}

ofParameter<ofRectangle> & ofParameterGroup::getRectangle(std::size_t pos) {
	return get<ofRectangle>(pos);
}

ofParameterGroup & ofParameterGroup::getGroup(std::size_t pos) {
	if (pos >= size()) {
		throw std::out_of_range(("get(): " + ofToString(pos) + "out of bounds").c_str());
	} else {
		if (getType(pos) == typeid(ofParameterGroup).name()) {
			return *static_cast<ofParameterGroup *>(obj->parameters[pos].get());
		} else {
			throw std::runtime_error(("get():  bad type for pos " + ofToString(pos) + ", returning empty group").c_str());
		}
	}
}

std::size_t ofParameterGroup::size() const {
	return obj->parameters.size();
}

std::string ofParameterGroup::getName(std::size_t position) const {
	if (position >= size()) {
		ofLogVerbose("ofParameterGroup::getName") << "attempt at accessing index larger than contained " << position;
		return "";
	} else {
		return obj->parameters[position]->getName();
	}
}

std::string ofParameterGroup::getType(std::size_t position) const {
	if (position >= size()) {
		ofLogVerbose("ofParameterGroup::getType") << "attempt at accessing index larger than contained " << position;
		return "";
	} else {
		return obj->parameters[position]->type();
	}
}

int ofParameterGroup::getPosition(const std::string & name) const {
	auto escaped_name = escape(name);
	if (contains(escaped_name)) {
		return obj->parametersIndex.find(escaped_name)->second;
	} else {
		ofLogVerbose("ofParameterGroup::getPosition") << "attempt at getting position of non-contained name " << name;
		return -1;
	}
}

std::string ofParameterGroup::getName() const {
	return obj->name;
}

bool ofParameterGroup::setName(const std::string & name){
	std::string oldName = getName();
	if (escape(name) == escape(oldName)) return false;
	if (!ofParameterGroup::changeChildName(this, obj->parents, escape(oldName), escape(name))) {
		setName(oldName);
		return false;
	}
	obj->name = name;
	return true;
}

std::string ofParameterGroup::getEscapedName() const {
	if (getName() == "") {
		return "group";
	} else {
		return ofAbstractParameter::getEscapedName();
	}
}

std::string ofParameterGroup::toString() const {
	std::stringstream out;
	out << *this;
	return out.str();
}

void ofParameterGroup::fromString(const std::string & name) {
	ofLogWarning() << "ofParameterGroup doesn't implement fromString yet";
}

const ofAbstractParameter & ofParameterGroup::get(const std::string & name) const {
	auto it = obj->parametersIndex.find(escape(name));
	std::size_t index = it->second;
	return get(index);
}

const ofAbstractParameter & ofParameterGroup::get(std::size_t pos) const {
	return *obj->parameters[pos];
}

const ofAbstractParameter & ofParameterGroup::operator[](const std::string & name) const {
	return get(name);
}

const ofAbstractParameter & ofParameterGroup::operator[](std::size_t pos) const {
	return get(pos);
}

ofAbstractParameter & ofParameterGroup::get(const std::string & name) {
	auto it = obj->parametersIndex.find(escape(name));
	std::size_t index = it->second;
	return get(index);
}

ofAbstractParameter & ofParameterGroup::get(std::size_t pos) {
	return *obj->parameters[pos];
}

ofAbstractParameter & ofParameterGroup::operator[](const std::string & name) {
	return get(name);
}

ofAbstractParameter & ofParameterGroup::operator[](std::size_t pos) {
	return get(pos);
}

std::ostream & operator<<(std::ostream & os, const ofParameterGroup & group) {
	std::streamsize width = os.width();
	for (std::size_t i = 0; i < group.size(); i++) {
		if (group.getType(i) == typeid(ofParameterGroup).name()) {
			os << group.getName(i) << ":" << std::endl;
			os << std::setw(width + 4);
			os << group.getGroup(i);
		} else {
			os << group.getName(i) << ":" << group.get(i) << std::endl;
			os << std::setw(width);
		}
	}
	return os;
}

bool ofParameterGroup::contains(const std::string & name) const {
	return obj->parametersIndex.find(escape(name)) != obj->parametersIndex.end();
}

void ofParameterGroup::Value::notifyParameterChanged(ofAbstractParameter & param) {
	ofNotifyEvent(parameterChangedE, param);
	parents.erase(std::remove_if(parents.begin(), parents.end(), [&param](const std::weak_ptr<Value> & p) {
		auto parent = p.lock();
		if (parent) parent->notifyParameterChanged(param);
		return !parent;
	}),
		parents.end());
}

void ofParameterGroup::Value::notifyParameterNameChanged(ofAbstractParameter & param)
{
	ofNotifyEvent(childNameChangedEvent,param);
	parents.erase(std::remove_if(parents.begin(),parents.end(),[&param](const std::weak_ptr<Value> & p){
		auto parent = p.lock();
		if(parent) parent->notifyParameterNameChanged(param);
		return !parent;
	}),parents.end());
}
			
bool ofParameterGroup::Value::updateParameterName(const std::string oldName, const std::string newName){
	if(parametersIndex.find(newName) != parametersIndex.end()){
		return false;
	}
	if(oldName != newName){
		parametersIndex[newName] = parametersIndex[oldName];
		parametersIndex.erase(oldName);
		return true;
	}
	return false;
}

const ofParameterGroup ofParameterGroup::getFirstParent() const{
	auto first = std::find_if(obj->parents.begin(),obj->parents.end(),[](const std::weak_ptr<Value> & p){return p.lock()!=nullptr;});
	if(first!=obj->parents.end()){
		return first->lock();
	} else {
		return std::shared_ptr<Value>(nullptr);
	}
}

ofEvent<ofAbstractParameter> & ofParameterGroup::parameterChangedE() {
	return obj->parameterChangedE;
}

ofAbstractParameter & ofParameterGroup::back() {
	return *obj->parameters.back();
}

ofAbstractParameter & ofParameterGroup::front() {
	return *obj->parameters.front();
}

const ofAbstractParameter & ofParameterGroup::back() const {
	return *obj->parameters.back();
}

const ofAbstractParameter & ofParameterGroup::front() const {
	return *obj->parameters.front();
}

void ofParameterGroup::setSerializable(bool _serializable) {
	obj->serializable = _serializable;
}

bool ofParameterGroup::isSerializable() const {
	return obj->serializable;
}

bool ofParameterGroup::isReadOnly() const {
	return false;
}

const void * ofParameterGroup::getInternalObject() const {
	return obj.get();
}

std::shared_ptr<ofAbstractParameter> ofParameterGroup::newReference() const {
	return std::make_shared<ofParameterGroup>(*this);
}

void ofParameterGroup::setParent(ofParameterGroup & parent) {
	obj->parents.emplace_back(parent.obj);
}

ofParameterGroup::operator bool() const {
	return obj != nullptr;
}

std::vector<std::shared_ptr<ofAbstractParameter> >::iterator ofParameterGroup::begin(){
	return obj->parameters.begin();
}

std::vector<std::shared_ptr<ofAbstractParameter> >::iterator ofParameterGroup::end(){
	return obj->parameters.end();
}

std::vector<std::shared_ptr<ofAbstractParameter> >::const_iterator ofParameterGroup::begin() const{
	return obj->parameters.begin();
}

std::vector<std::shared_ptr<ofAbstractParameter> >::const_iterator ofParameterGroup::end() const{
	return obj->parameters.end();
}

std::vector<std::shared_ptr<ofAbstractParameter> >::reverse_iterator ofParameterGroup::rbegin(){
	return obj->parameters.rbegin();
}

std::vector<std::shared_ptr<ofAbstractParameter> >::reverse_iterator ofParameterGroup::rend(){
	return obj->parameters.rend();
}

std::vector<std::shared_ptr<ofAbstractParameter> >::const_reverse_iterator ofParameterGroup::rbegin() const{
	return obj->parameters.rbegin();
}

std::vector<std::shared_ptr<ofAbstractParameter> >::const_reverse_iterator ofParameterGroup::rend() const{
	return obj->parameters.rend();
}


void ofParameterGroup::checkAndRemoveExpiredParents(std::vector<std::weak_ptr<Value>> & parents)
{
	parents.erase(std::remove_if(parents.begin(),
				   parents.end(),
				   [](const std::weak_ptr<Value> & p){ return p.expired(); }),
	parents.end());
}


bool ofParameterGroup::changeChildName(ofAbstractParameter* child, std::vector<std::weak_ptr<Value>> & parents, const std::string& oldName, std::string newName)
{
	if(!child) return false;
	
	// name has not change, no need to notify anything
	if(oldName == newName) return false;
	
	checkAndRemoveExpiredParents(parents);
	
	for(auto parent = parents.begin(); parent != parents.end(); ++parent){
		auto p = parent->lock();
		if(p){
			if(!p->updateParameterName(oldName, newName)){
				// Undo the name change in the paremeters that we already did
				for(auto reverseParent = parent-1; reverseParent != parents.begin()-1; --reverseParent){
					auto rp = reverseParent->lock();
					if(rp){
						rp->updateParameterName(newName, oldName);
					}
				}
				return false;
			}
		}
	}
		
	ofNotifyEvent(child->nameChangedEvent(), newName, child);
	

	// we notify to the parents after updating the name in order to avoid any possible data race
	for(auto & parent: parents){
		auto p = parent.lock();
		if(p){
			p->notifyParameterNameChanged(*child);
		}
	}
	return true;
}

ofEvent<std::string>& ofParameterGroup::nameChangedEvent()
{
	return obj->nameChangedEvent;
}
ofEvent<ofAbstractParameter>& ofParameterGroup::childNameChangedEvent()
{
	return obj->childNameChangedEvent;
}
