#include "rendercontext.h"
#include "svgelementhead.h"
#include "svgelementtail.h"
#include "svgcolor.h"
#include "svglength.h"
#include "svglengthlist.h"
#include "svgnumber.h"
#include "paint.h"
#include "strokedata.h"

namespace lunasvg {

RenderStyle::RenderStyle()
{
    m_properties.fill(nullptr);
}

void RenderStyle::add(const CSSPropertyList* items)
{
    for(unsigned int i = 0;i < MAX_STYLE;i++)
    {
        const CSSPropertyBase* item = items->getItem(CSSPropertyID(i));
        if(item == nullptr || item->isInherited())
            continue;
        m_properties[i] = item->property();
    }
}

void RenderStyle::add(const DOMSVGStyle& style)
{
    if(style.isSpecified())
        add(style.property());
}

void RenderStyle::add(const RenderStyle& style)
{
    for(unsigned int i = 0;i < MAX_STYLE;i++)
        if(style.m_properties[i])
            m_properties[i] = style.m_properties[i];
}

void RenderStyle::inheritFrom(const RenderStyle& style)
{
    for(unsigned int i = 0;i < MAX_STYLE;i++)
    {
        if(style.m_properties[i] == nullptr)
            continue;

        switch(i)
        {
        case CSSPropertyIdDisplay:
        case CSSPropertyIdClip:
        case CSSPropertyIdClip_Path:
        case CSSPropertyIdOverflow:
        case CSSPropertyIdStop_Color:
        case CSSPropertyIdStop_Opacity:
        case CSSPropertyIdSolid_Color:
        case CSSPropertyIdSolid_Opacity:
        case CSSPropertyIdOpacity:
        case CSSPropertyIdMask:
            break;
        default:
            m_properties[i] = style.m_properties[i];
            break;
        }
    }
}

void RenderStyle::set(const CSSPropertyBase* item)
{
    if(!item->isInherited())
        m_properties[item->propertyId()] = item->property();
}

void RenderStyle::clear(CSSPropertyID nameId)
{
    m_properties[nameId] = nullptr;
}

void RenderStyle::clearAll()
{
    m_properties.fill(nullptr);
}

bool RenderStyle::isDisplayNone() const
{
    if(const SVGProperty* property = get(CSSPropertyIdDisplay))
    {
        const SVGEnumeration<Display>* display = to<SVGEnumeration<Display>>(property);
        return display->enumValue() == DisplayNone;
    }

    return false;
}

bool RenderStyle::isHidden() const
{
    if(const SVGProperty* property = get(CSSPropertyIdVisibility))
    {
        const SVGEnumeration<Visibility>* visibility = to<SVGEnumeration<Visibility>>(property);
        return visibility->enumValue() == VisibilityHidden;
    }

    return false;
}

bool RenderStyle::hasStroke() const
{
    if(const SVGProperty* property = get(CSSPropertyIdStroke))
        return to<SVGPaint>(property)->colorType() != ColorTypeNone;

    return false;
}

bool RenderStyle::hasFill() const
{
    if(const SVGProperty* property = get(CSSPropertyIdFill))
        return to<SVGPaint>(property)->colorType() != ColorTypeNone;

    return false;
}

StrokeData RenderStyle::strokeData(const RenderState& state) const
{
    StrokeData strokeData;
    if(const SVGProperty* property = get(CSSPropertyIdStroke_Width))
        strokeData.setWidth(to<SVGLength>(property)->value(state));
    if(const SVGProperty* property = get(CSSPropertyIdStroke_Miterlimit))
        strokeData.setMiterLimit(to<SVGNumber>(property)->value());
    if(const SVGProperty* property = get(CSSPropertyIdStroke_Linecap))
        strokeData.setCap(to<SVGEnumeration<LineCap>>(property)->enumValue());
    if(const SVGProperty* property = get(CSSPropertyIdStroke_Linejoin))
        strokeData.setJoin(to<SVGEnumeration<LineJoin>>(property)->enumValue());
    if(const SVGProperty* property = get(CSSPropertyIdStroke_Dasharray))
        strokeData.setDash(to<SVGLengthList>(property)->values(state));
    if(const SVGProperty* property = get(CSSPropertyIdStroke_Dashoffset))
        strokeData.setDashOffset(to<SVGLength>(property)->value(state));

    return strokeData;
}

Paint RenderStyle::fillPaint(const RenderState& state) const
{
    if(const SVGProperty* property = get(CSSPropertyIdFill))
        return to<SVGPaint>(property)->getPaint(state);

    return KRgbBlack;
}

Paint RenderStyle::strokePaint(const RenderState& state) const
{
    if(const SVGProperty* property = get(CSSPropertyIdStroke))
        return to<SVGPaint>(property)->getPaint(state);

    return Paint();
}

double RenderStyle::strokeWidth(const RenderState& state) const
{
    if(const SVGProperty* property = get(CSSPropertyIdStroke_Width))
        return to<SVGLength>(property)->value(state);

    return 1.0;
}

double RenderStyle::fillOpacity() const
{
    if(const SVGProperty* property = get(CSSPropertyIdFill_Opacity))
        return to<SVGNumber>(property)->value();

    return 1.0;
}

double RenderStyle::strokeOpacity() const
{
    if(const SVGProperty* property = get(CSSPropertyIdStroke_Opacity))
        return to<SVGNumber>(property)->value();

    return 1.0;
}

double RenderStyle::opacity() const
{
    if(const SVGProperty* property = get(CSSPropertyIdOpacity))
        return to<SVGNumber>(property)->value();

    return 1.0;
}

const std::string& RenderStyle::mask() const
{
    if(const SVGProperty* property = get(CSSPropertyIdMask))
        return to<SVGString>(property)->value();

    return KEmptyString;
}

const std::string& RenderStyle::clipPath() const
{
    if(const SVGProperty* property = get(CSSPropertyIdClip_Path))
        return to<SVGString>(property)->value();

    return KEmptyString;
}

const std::string& RenderStyle::markerStart() const
{
    if(const SVGProperty* property = get(CSSPropertyIdMarker_Start))
        return to<SVGString>(property)->value();

    return KEmptyString;
}

const std::string& RenderStyle::markerMid() const
{
    if(const SVGProperty* property = get(CSSPropertyIdMarker_Mid))
        return to<SVGString>(property)->value();

    return KEmptyString;
}

const std::string& RenderStyle::markerEnd() const
{
    if(const SVGProperty* property = get(CSSPropertyIdMarker_End))
        return to<SVGString>(property)->value();

    return KEmptyString;
}

WindRule RenderStyle::fillRule() const
{
    if(const SVGProperty* property = get(CSSPropertyIdFill_Rule))
        return to<SVGEnumeration<WindRule>>(property)->enumValue();

    return WindRuleNonZero;
}

WindRule RenderStyle::clipRule() const
{
    if(const SVGProperty* property = get(CSSPropertyIdClip_Rule))
        return to<SVGEnumeration<WindRule>>(property)->enumValue();

    return WindRuleNonZero;
}

std::set<const SVGElementImpl*> RenderBreaker::renderBreaker;

void RenderBreaker::registerElement(const SVGElementImpl* element)
{
    renderBreaker.insert(element);
}

void RenderBreaker::unregisterElement(const SVGElementImpl* element)
{
    renderBreaker.erase(element);
}

bool RenderBreaker::hasElement(const SVGElementImpl* element)
{
    return renderBreaker.find(element) != renderBreaker.end();
}

RenderContext::~RenderContext()
{
    assert(m_states.empty());
    delete m_state;
}

RenderContext::RenderContext(const SVGElementImpl* element, RenderMode mode) :
    m_mode(mode),
    m_state(new RenderState()),
    m_current(element)
{
}

void RenderContext::push()
{
    RenderState* newState = new RenderState();
    newState->element = m_current;
    newState->canvas = m_state->canvas;
    newState->matrix = m_state->matrix;
    newState->style.inheritFrom(m_state->style);
    newState->viewPort = m_state->viewPort;
    newState->bbox = Rect(0, 0, 0, 0);
    newState->color = m_state->color;
    newState->dpi = m_state->dpi;

    m_states.push(m_state);
    m_state = newState;
}

void RenderContext::pop()
{
    RenderState* newState = m_states.top();
    Rect bbox = newState->matrix.inverted().multiply(m_state->matrix).mapRect(m_state->bbox);

    double l = std::min(newState->bbox.x, bbox.x);
    double t = std::min(newState->bbox.y, bbox.y);
    double r = std::max(newState->bbox.x + newState->bbox.width, bbox.x + bbox.width);
    double b = std::max(newState->bbox.y + newState->bbox.height, bbox.y + bbox.height);

    newState->bbox.x = l;
    newState->bbox.y = t;
    newState->bbox.width = r - l;
    newState->bbox.height = b - t;

    delete m_state;
    m_state = newState;
    m_states.pop();
}

void RenderContext::skipElement()
{
    assert(m_current->isSVGElementHead());
    m_current = to<SVGElementHead>(m_current)->tail;
}

void RenderContext::render(const SVGElementImpl* head, const SVGElementImpl* tail)
{
    m_current = head;
    m_current->render(*this);
    while(m_current != tail)
    {
        m_current = m_current->next;
        m_current->render(*this);
    }
}

} // namespace lunasvg
