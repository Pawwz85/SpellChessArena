#pragma once

#include <vector>
#include <QString>
#include <QUrl>

namespace SpriteSet {

   class SpriteSetScheme {
      public:

      struct SpriteDef {
         QString spriteIdentifier;
         QUrl url;
      };

      protected:
         std::vector<SpriteDef> defs; 
      public:
      SpriteSetScheme() = default;
      SpriteSetScheme(const std::vector<SpriteDef> & definitions);
      virtual ~SpriteSetScheme() = default;

      void setDefinitions(const std::vector<SpriteDef> & definitions);
      void copyFromOther(const SpriteSetScheme & other);
      const std::vector<SpriteDef> & getDefinitions() const;
      const QUrl * findSpriteUrl(const QString & spriteIdentifier) const;
      bool validateOther(const SpriteSetScheme & other) const;
      bool isEmpty() const;
   };

};