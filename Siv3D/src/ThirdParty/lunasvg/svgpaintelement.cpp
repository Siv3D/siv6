#include "svgpaintelement.h"

namespace lunasvg {

SVGPaintElement::SVGPaintElement(ElementID elementId, SVGDocument* document) :
    SVGStyledElement(elementId, document)
{
}

void SVGPaintElement::render(RenderContext& context) const
{
    context.skipElement();
}

} // namespace lunasvg
