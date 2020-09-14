(function ($) {
    $(document).ready(function () {
        $('.post-carrusel .grid-items').slick({
            infinite: true,
            //arrows: false,
            dots: true,
            slidesToShow: 4,
            slidesToScroll: 4,
            centerPadding: '60px',
            responsive: [{
                breakpoint: 980,
                settings: {
                    slidesToShow: 1,
                    slidesToScroll: 1,
                    infinite: true,
                    dots: true
                }
            }]
        });
        var slides = $('.slick-slide, .skin.flat .layer-content');
        var slidesHeight = Array.prototype.map.call(slides, function (sl) {
            return sl.clientHeight + 160;
        });
        var maxHeight = Math.max.apply(null, slidesHeight);
        Array.prototype.forEach.call(slides, function (sl) {
            sl.style.height = maxHeight + "px";
        });
    });
})(jQuery);