icu_ver ?= icu4c-64_2
icu_data_url ?= https://github.com/unicode-org/icu/releases/download/release-64-2/${icu_ver}-data.zip
icu_docs_url ?= https://github.com/unicode-org/icu/releases/download/release-64-2/${icu_ver}-docs.zip
icu_src_url ?= https://github.com/unicode-org/icu/releases/download/release-64-2/${icu_ver}-src.tgz

icu:

icu-fetch:
	mkdir -p build/src cache/
	[ -f cache/${icu_ver}-data.zip ] || (cd cache; wget ${icu_data_url})
	[ -f cache/${icu_ver}-data.zip.asc ] || (cd cache; wget ${icu_data_url}.asc)
	[ -f cache/${icu_ver}-docs.zip ] || (cd cache; wget ${icu_docs_url})
	[ -f cache/${icu_ver}-docs.zip.asc ] || (cd cache; wget ${icu_docs_url}.asc)
	[ -f cache/${icu_ver}-src.tgz ] || (cd cache; wget ${icu_src_url})
	[ -f cache/${icu_ver}-src.tgz.asc ] || (cd cache; wget ${icu_src_url}.asc)
