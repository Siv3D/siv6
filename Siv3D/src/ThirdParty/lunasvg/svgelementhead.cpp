#include "svgelementhead.h"
#include "svgdocumentimpl.h"
#include "svgelementtail.h"
#include "rendercontext.h"

namespace lunasvg {

SVGElementHead::SVGElementHead(ElementID elementId, SVGDocument* document) :
    SVGElementImpl(document),
    m_elementId(elementId)
{
}

SVGElementHead::~SVGElementHead()
{
    document()->impl()->updateIdCache(m_id, KEmptyString, this);
}

const std::string& SVGElementHead::tagName() const
{
    return Utils::elementName(m_elementId);
}

void SVGElementHead::setAttribute(const std::string& name, const std::string& value)
{
    DOMPropertyID nameId = Utils::domPropertyId(name);
    if(nameId!=DOMPropertyIdUnknown)
        setProperty(nameId, value);
}

std::string SVGElementHead::getAttribute(const std::string& name) const
{
    DOMPropertyID nameId = Utils::domPropertyId(name);
    if(nameId!=DOMPropertyIdUnknown)
        return getProperty(nameId);

    return KEmptyString;
}

bool SVGElementHead::hasAttribute(const std::string& name) const
{
    DOMPropertyID nameId = Utils::domPropertyId(name);
    if(nameId!=DOMPropertyIdUnknown)
        return hasProperty(nameId);

    return false;
}

void SVGElementHead::removeAttribute(const std::string& name)
{
    DOMPropertyID nameId = Utils::domPropertyId(name);
    if(nameId!=DOMPropertyIdUnknown)
        removeProperty(nameId);
}

void SVGElementHead::externalise(std::string& out, std::uint32_t& indent) const
{
    out.append(indent, '\t');
    out += '<';
    out += Utils::elementName(m_elementId);
    if(isSVGRootElement())
    {
        out += ' ';
        out += "xmlns";
        out += '=';
        out += '"';
        out += "http://www.w3.org/2000/svg";
        out += '"';
        out += ' ';
        out += "xmlns:xlink";
        out += '=';
        out += '"';
        out += "http://www.w3.org/1999/xlink";
        out += '"';
        out += ' ';
        out += "version";
        out += '=';
        out += '"';
        out += "1.1";
        out += '"';
    }

    if(!m_id.empty())
    {
        out += ' ';
        out += "id";
        out += '=';
        out += '"';
        out += m_id;
        out += '"';
    }

    for(unsigned i=0;i<m_properties.size();i++)
    {
        if(!m_properties[i]->isSpecified())
            continue;

        out += ' ';
        out += Utils::domPropertyName(m_properties[i]->propertyId());
        out += '=';
        out += '"';
        out += m_properties[i]->propertyAsString();
        out += '"';
    }

    if(next == tail)
    {
        out += '/';
        out += '>';
        out += '\n';
    }
    else
    {
        indent++;
        out += '>';
        out += '\n';
    }
}

void SVGElementHead::externaliseTail(std::string& out, std::uint32_t& indent) const
{
    if(next == tail)
        return;

    indent--;
    out.append(indent, '\t');
    out += '<';
    out += '/';
    out += Utils::elementName(m_elementId);
    out += '>';
    out += '\n';
}

std::string SVGElementHead::getProperty(DOMPropertyID nameId) const
{
    if(nameId==DOMPropertyIdId)
        return m_id;

    for(unsigned i=0;i<m_properties.size();i++)
        if(nameId==m_properties[i]->propertyId())
            return m_properties[i]->propertyAsString();

    return KEmptyString;
}

bool SVGElementHead::hasProperty(DOMPropertyID nameId) const
{
    if(nameId==DOMPropertyIdId)
        return !m_id.empty();

    for(unsigned i=0;i<m_properties.size();i++)
        if(nameId==m_properties[i]->propertyId())
            return m_properties[i]->isSpecified();

    return false;
}

void SVGElementHead::setProperty(DOMPropertyID nameId, const std::string& value)
{
    if(nameId==DOMPropertyIdId)
    {
        updateId(value);
        return;
    }

    for(unsigned i=0;i<m_properties.size();i++)
        if(nameId==m_properties[i]->propertyId())
            return m_properties[i]->setPropertyAsString(value);
}

void SVGElementHead::removeProperty(DOMPropertyID nameId)
{
    if(nameId==DOMPropertyIdId)
    {
        updateId(KEmptyString);
        return;
    }

    for(unsigned i=0;i<m_properties.size();i++)
        if(nameId==m_properties[i]->propertyId())
            return m_properties[i]->resetProperty();
}

void SVGElementHead::render(RenderContext&) const
{
}

void SVGElementHead::renderTail(RenderContext&) const
{
}

DOMSVGPropertyBase* SVGElementHead::findAnimatedProperty(DOMPropertyID nameId) const
{
    for(unsigned i=0;i<m_properties.size();i++)
        if(nameId==m_properties[i]->propertyId())
            return m_properties[i];

    return nullptr;
}

void SVGElementHead::addToPropertyMap(DOMSVGPropertyBase& property)
{
    m_properties.push_back(&property);
}

void SVGElementHead::updateId(const std::string& newValue)
{
    SVGDocumentImpl* impl = document()->impl();
    impl->updateIdCache(m_id, newValue, this);
    m_id.assign(newValue);
}

void SVGElementHead::baseClone(SVGElementHead& e) const
{
    e.updateId(m_id);
    for(unsigned i=0;i<m_properties.size();i++)
        e.m_properties[i]->clone(m_properties[i]);
}

} // namespace lunasvg
