/* Copyright (C) 2011-2013 Research In Motion Limited. Proprietary and confidential. */

#ifndef cascades_titlebarkind_h
#define cascades_titlebarkind_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
namespace cascades {

   /*!
    * 
    * @brief A class that represents the different types of a @c TitleBar.
    *
    * The supported types of a TitleBar include @c %Default, @c %Segmented, and @c %FreeForm.
    *
    * The @c %Default type supports title text, as well as the @c %acceptAction and @c %dismissAction elements.
    *
    * The @c %Segmented type supports options, as well as the @c %selectedIndex and @c %selectedOption elements.
    *
    * The @c %FreeForm type supports an indicator used to toggle between expanded and collapsed states. In addition,
    * @c %FreeForm supports an indicator toggle area, a content area where you can place controls, and an expandable
    * area where you can place controls.
    *
    * All types support the @c %appearance and @c %scrollBehavior properties.
    *
    * @xmlonly
    * <apigrouping group="User interface/Application structure"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.0.0
    */
  class BBCASCADES_EXPORT TitleBarKind {
    Q_GADGET
    Q_ENUMS (Type)

    public:

     /*!
      * @brief Specifies the different types of a @c TitleBar.
      *
      * @since BlackBerry 10.0.0
      */
      enum Type {
        /*! @brief Default for a @c TitleBar.
         *
         * @since BlackBerry 10.0.0
         */
        Default,
        /*! @brief A @c TitleBar with options.
         *
         * @since BlackBerry 10.0.0
         */
        Segmented,
        /*! 
         * @brief A @c TitleBar with free-form content. 
         *
         * @since BlackBerry 10.0.0
         */
        FreeForm
      };

    private:

      TitleBarKind();
      ~TitleBarKind();
  };
}
}

#endif // cascades_titlebarkind_h
