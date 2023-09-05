#!/bin/sh -e

BUILD_DEFAULT="$(date +%s)"
PREFIX_DEFAULT="NiboRoboLib-*"

echo_debug() {
    if [ -n "$DEBUG" ]; then
        echo "D: $1"
    fi
}

echo_error() {
    echo "E: $1"

    if [ -n "$2" ]; then
        exit "$2"
    fi
}

echo_info() {
    echo "I: $1"
}

echo_usage() {
    echo "usage: $0 <VERSION> [PREFIX] [-h|--help]"
    echo
    echo "Arguments"
    echo "========="
    echo
    echo "VERSION   The sementic version to update the packages to."
    echo "          If VERSION does not contain build meta, the contents of BUILD"
    echo "          are appended to VERSION automatically (separated by '+')."
    echo "          Example: '3.4.0', '3.4.1-rc.1' or '3.4.0+1693925980'"
    echo
    echo "BUILD     The build meta of the version (i.e. after the '+')."
    echo "          Default: 'date +%s' (current epoch, e.g. $BUILD_DEFAULT)"
    echo
    echo "PREFIX    A prefix to match the packages to update against."
    echo "          While matching, PREFIX is expanded as a shell expression."
    echo "          Default: '$PREFIX_DEFAULT' (all packages)"
    echo
    echo "Options"
    echo "======="
    echo
    echo "-h --help     Show this help/usage message."
    echo
}

case "$*" in
*"-h"* | *"--help"*)
    echo_usage
    exit
    ;;
esac

VERSION="$1"

if [ -z "$VERSION" ]; then
    echo_usage

    echo_error "The argument VERSION must be specified" 1
fi

case "$VERSION" in
*"+"*)
    echo_info "Ignoring argument BUILD since VERSION already contains build meta information"
    ;;
*)
    BUILD="$2"
    BUILD="${BUILD:-"$BUILD_DEFAULT"}"

    VERSION="$VERSION+$BUILD"
    ;;
esac

BRANCH="v$(echo "$VERSION" | cut -d'+' -f1)"

PREFIX="$3"
PREFIX="${PREFIX:-"$PREFIX_DEFAULT"}"

packages=0
for package in $PREFIX; do
    echo_debug "├── $package"

    file="$package/library.json"
    file_temp=$(mktemp)

    echo_debug "│   └── library.json"

    echo_debug "│       ├── version = $VERSION"
    jq --arg version "$VERSION" '.version = $version' "$file" >"$file_temp"

    echo_debug "│       └── repository.branch = $BRANCH"
    jq --arg branch "$BRANCH" '.repository.branch = $branch' "$file_temp" >"$file"

    packages=$((packages + 1))
done

echo_info "Updated $packages package(s) to version '$VERSION'"
