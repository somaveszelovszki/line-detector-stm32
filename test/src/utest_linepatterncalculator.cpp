#include <micro/math/numeric.hpp>
#include <micro/test/utils.hpp>
#include <LinePatternCalculator.hpp>

using namespace micro;

namespace {

typedef vec<Lines, 500> LineDetections;
typedef vec<LinePattern, 10> LinePatterns;

void test(const linePatternDomain_t domain, const LineDetections& lineDetections, const LinePatterns& expectedPatterns) {
    LinePatternCalculator calc;
    LinePatterns patterns;

    uint8_t lineId = 0;

    for (uint32_t i = 0; i < lineDetections.size(); ++i) {
        const centimeter_t distance = centimeter_t(i);
        Lines lines = lineDetections[i];

        // Sets different line identifiers for each line in each iteration
        // to prevent main line search from line id optimization.
        for (Line& line : lines) {
            line.id = ++lineId;
        }

        calc.update(domain, lines, distance, Sign::POSITIVE);

        const LinePattern& currentPattern = calc.pattern();
        if (patterns.empty() || *patterns.back() != currentPattern) {
            patterns.push_back(currentPattern);
        }
    }

    ASSERT_EQ(expectedPatterns.size(), patterns.size());
    for (uint32_t i = 0; i < patterns.size(); ++i) {
        EXPECT_EQ(expectedPatterns[i], patterns[i]);
    }
}

} // namespace

TEST(LinePatternCalculator, SINGLE_LINE) {

    const LineDetections lineDetections = {
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } }
    };

    const LinePatterns& expectedPatterns = {
        { LinePattern::type_t::SINGLE_LINE, Sign::NEUTRAL, Direction::CENTER }
    };

    test(linePatternDomain_t::Race, lineDetections, expectedPatterns);
}

TEST(LinePatternCalculator, NONE) {

    const LineDetections lineDetections = {
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {}
    };

    const LinePatterns& expectedPatterns = {
        { LinePattern::type_t::SINGLE_LINE, Sign::NEUTRAL, Direction::CENTER },
        { LinePattern::type_t::NONE,        Sign::NEUTRAL, Direction::CENTER }
    };

    test(linePatternDomain_t::Race, lineDetections, expectedPatterns);
}

TEST(LinePatternCalculator, BRAKE) {

    const LineDetections lineDetections = {
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } }
    };

    const LinePatterns& expectedPatterns = {
        { LinePattern::type_t::SINGLE_LINE, Sign::NEUTRAL, Direction::CENTER },
        { LinePattern::type_t::BRAKE,       Sign::NEUTRAL, Direction::CENTER }
    };

    test(linePatternDomain_t::Race, lineDetections, expectedPatterns);
}

TEST(LinePatternCalculator, ACCELERATION) {

    const LineDetections lineDetections = {
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } }
    };

    const LinePatterns& expectedPatterns = {
        { LinePattern::type_t::SINGLE_LINE, Sign::NEUTRAL, Direction::CENTER },
        { LinePattern::type_t::ACCELERATE,  Sign::NEUTRAL, Direction::CENTER }
    };

    test(linePatternDomain_t::Race, lineDetections, expectedPatterns);
}

TEST(LinePatternCalculator, ACCELERATION_noisy) {

    const LineDetections lineDetections = {
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) } }
    };

    const LinePatterns& expectedPatterns = {
        { LinePattern::type_t::SINGLE_LINE, Sign::NEUTRAL, Direction::CENTER },
        { LinePattern::type_t::ACCELERATE,  Sign::NEUTRAL, Direction::CENTER }
    };

    test(linePatternDomain_t::Race, lineDetections, expectedPatterns);
}

TEST(LinePatternCalculator, JUNCTION_2_NEGATIVE_LEFT_TO_JUNCTION_2_POSITIVE_RIGHT) {

    const LineDetections lineDetections = {
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(-83) }, { millimeter_t(0) } },
        { { millimeter_t(-79) }, { millimeter_t(0) } },
        { { millimeter_t(-76) }, { millimeter_t(0) } },
        { { millimeter_t(-73) }, { millimeter_t(0) } },
        { { millimeter_t(-70) }, { millimeter_t(0) } },
        { { millimeter_t(-68) }, { millimeter_t(0) } },
        { { millimeter_t(-66) }, { millimeter_t(0) } },
        { { millimeter_t(-64) }, { millimeter_t(0) } },
        { { millimeter_t(-62) }, { millimeter_t(0) } },
        { { millimeter_t(-60) }, { millimeter_t(0) } },
        { { millimeter_t(-58) }, { millimeter_t(0) } },
        { { millimeter_t(-57) }, { millimeter_t(0) } },
        { { millimeter_t(-56) }, { millimeter_t(0) } },
        { { millimeter_t(-55) }, { millimeter_t(0) } },
        { { millimeter_t(-54) }, { millimeter_t(0) } },
        { { millimeter_t(-53) }, { millimeter_t(0) } },
        { { millimeter_t(-52) }, { millimeter_t(0) } },
        { { millimeter_t(-51) }, { millimeter_t(0) } },
        { { millimeter_t(-50) }, { millimeter_t(0) } },
        { { millimeter_t(-49) }, { millimeter_t(0) } },
        { { millimeter_t(-48) }, { millimeter_t(0) } },
        { { millimeter_t(-47) }, { millimeter_t(0) } },
        { { millimeter_t(-46) }, { millimeter_t(0) } },
        { { millimeter_t(-45) }, { millimeter_t(0) } },
        { { millimeter_t(-44) }, { millimeter_t(0) } },
        { { millimeter_t(-43) }, { millimeter_t(0) } },
        { { millimeter_t(-42) }, { millimeter_t(0) } },
        { { millimeter_t(-41) }, { millimeter_t(0) } },
        { { millimeter_t(-40) }, { millimeter_t(0) } },
        { { millimeter_t(-39) }, { millimeter_t(0) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(39) } },
        { { millimeter_t(0) }, { millimeter_t(40) } },
        { { millimeter_t(0) }, { millimeter_t(41) } },
        { { millimeter_t(0) }, { millimeter_t(42) } },
        { { millimeter_t(0) }, { millimeter_t(43) } },
        { { millimeter_t(0) }, { millimeter_t(44) } },
        { { millimeter_t(0) }, { millimeter_t(45) } },
        { { millimeter_t(0) }, { millimeter_t(46) } },
        { { millimeter_t(0) }, { millimeter_t(47) } },
        { { millimeter_t(0) }, { millimeter_t(48) } },
        { { millimeter_t(0) }, { millimeter_t(49) } },
        { { millimeter_t(0) }, { millimeter_t(50) } },
        { { millimeter_t(0) }, { millimeter_t(51) } },
        { { millimeter_t(0) }, { millimeter_t(52) } },
        { { millimeter_t(0) }, { millimeter_t(53) } },
        { { millimeter_t(0) }, { millimeter_t(54) } },
        { { millimeter_t(0) }, { millimeter_t(55) } },
        { { millimeter_t(0) }, { millimeter_t(56) } },
        { { millimeter_t(0) }, { millimeter_t(57) } },
        { { millimeter_t(0) }, { millimeter_t(58) } },
        { { millimeter_t(0) }, { millimeter_t(60) } },
        { { millimeter_t(0) }, { millimeter_t(62) } },
        { { millimeter_t(0) }, { millimeter_t(64) } },
        { { millimeter_t(0) }, { millimeter_t(66) } },
        { { millimeter_t(0) }, { millimeter_t(68) } },
        { { millimeter_t(0) }, { millimeter_t(70) } },
        { { millimeter_t(0) }, { millimeter_t(73) } },
        { { millimeter_t(0) }, { millimeter_t(76) } },
        { { millimeter_t(0) }, { millimeter_t(79) } },
        { { millimeter_t(0) }, { millimeter_t(83) } }
    };

    const LinePatterns& expectedPatterns = {
        { LinePattern::type_t::SINGLE_LINE, Sign::NEUTRAL,  Direction::CENTER },
        { LinePattern::type_t::JUNCTION_2,  Sign::NEGATIVE, Direction::LEFT   },
        { LinePattern::type_t::JUNCTION_2,  Sign::POSITIVE, Direction::RIGHT  }
    };

    test(linePatternDomain_t::Labyrinth, lineDetections, expectedPatterns);
}

TEST(LinePatternCalculator, JUNCTION_1_NEGATIVE_CENTER_TO_JUNCTION_2_POSITIVE_RIGHT) {

    const LineDetections lineDetections = {
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) } },
        { { millimeter_t(-38) }, { millimeter_t(0) } },
        { { millimeter_t(-38) }, { millimeter_t(0) } },
        { { millimeter_t(-38) }, { millimeter_t(0) } },
        { { millimeter_t(-38) }, { millimeter_t(0) } },
        { { millimeter_t(-38) }, { millimeter_t(0) } },
        { { millimeter_t(-38) }, { millimeter_t(0) } },
        { { millimeter_t(-38) }, { millimeter_t(0) } },
        { { millimeter_t(-38) }, { millimeter_t(0) } },
        { { millimeter_t(-38) }, { millimeter_t(0) } },
        { { millimeter_t(-38) }, { millimeter_t(0) } },
        { { millimeter_t(-38) }, { millimeter_t(0) } },
        { { millimeter_t(-38) }, { millimeter_t(0) } },
        { { millimeter_t(-38) }, { millimeter_t(0) } },
        { { millimeter_t(-38) }, { millimeter_t(0) } },
        { { millimeter_t(-38) }, { millimeter_t(0) } },
        { { millimeter_t(-38) }, { millimeter_t(1) } },
        { { millimeter_t(-38) }, { millimeter_t(2) } },
        { { millimeter_t(-38) }, { millimeter_t(3) } },
        { { millimeter_t(-38) }, { millimeter_t(4) } },
        { { millimeter_t(-38) }, { millimeter_t(6) } },
        { { millimeter_t(-38) }, { millimeter_t(8) } },
        { { millimeter_t(-38) }, { millimeter_t(10) } },
        { { millimeter_t(-38) }, { millimeter_t(13) } },
        { { millimeter_t(-38) }, { millimeter_t(16) } },
        { { millimeter_t(-38) }, { millimeter_t(19) } },
        { { millimeter_t(-38) }, { millimeter_t(22) } },
        { { millimeter_t(-38) }, { millimeter_t(25) } },
        { { millimeter_t(-38) }, { millimeter_t(29) } },
        { { millimeter_t(-38) }, { millimeter_t(33) } },
        { { millimeter_t(-38) }, { millimeter_t(37) } },
        { { millimeter_t(-38) }, { millimeter_t(42) } },
        { { millimeter_t(-38) }, { millimeter_t(47) } },
        { { millimeter_t(-38) }, { millimeter_t(52) } },
        { { millimeter_t(-38) }, { millimeter_t(58) } },
        { { millimeter_t(-38) }, { millimeter_t(66) } },
        { { millimeter_t(-38) }, { millimeter_t(72) } },
        { { millimeter_t(-38) }, { millimeter_t(78) } },
        { { millimeter_t(-38) }, { millimeter_t(84) } },
        { { millimeter_t(-38) }, { millimeter_t(90) } },
        { { millimeter_t(-38) }, { millimeter_t(97) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) } },
        { { millimeter_t(-38) } }
    };

    const LinePatterns& expectedPatterns = {
        { LinePattern::type_t::SINGLE_LINE, Sign::NEUTRAL,  Direction::CENTER },
        { LinePattern::type_t::JUNCTION_1,  Sign::NEGATIVE, Direction::CENTER },
        { LinePattern::type_t::JUNCTION_2,  Sign::POSITIVE, Direction::RIGHT  },
        { LinePattern::type_t::SINGLE_LINE, Sign::NEUTRAL,  Direction::CENTER }
    };

    test(linePatternDomain_t::Labyrinth, lineDetections, expectedPatterns);
}

TEST(LinePatternCalculator, JUNCTION_3_NEGATIVE_LEFT_TO_JUNCTION_3_POSITIVE_CENTER) {

    const LineDetections lineDetections = {
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(-83) }, { millimeter_t(0) } },
        { { millimeter_t(-79) }, { millimeter_t(0) } },
        { { millimeter_t(-76) }, { millimeter_t(0) } },
        { { millimeter_t(-73) }, { millimeter_t(0) } },
        { { millimeter_t(-70) }, { millimeter_t(0) } },
        { { millimeter_t(-68) }, { millimeter_t(0) } },
        { { millimeter_t(-66) }, { millimeter_t(0) } },
        { { millimeter_t(-64) }, { millimeter_t(0) } },
        { { millimeter_t(-62) }, { millimeter_t(0) } },
        { { millimeter_t(-60) }, { millimeter_t(0) } },
        { { millimeter_t(-58) }, { millimeter_t(0) } },
        { { millimeter_t(-57) }, { millimeter_t(0) } },
        { { millimeter_t(-120) }, { millimeter_t(-56) }, { millimeter_t(0) } },
        { { millimeter_t(-116) }, { millimeter_t(-55) }, { millimeter_t(0) } },
        { { millimeter_t(-112) }, { millimeter_t(-54) }, { millimeter_t(0) } },
        { { millimeter_t(-108) }, { millimeter_t(-53) }, { millimeter_t(0) } },
        { { millimeter_t(-104) }, { millimeter_t(-52) }, { millimeter_t(0) } },
        { { millimeter_t(-102) }, { millimeter_t(-51) }, { millimeter_t(0) } },
        { { millimeter_t(-100) }, { millimeter_t(-50) }, { millimeter_t(0) } },
        { { millimeter_t(-98) }, { millimeter_t(-49) }, { millimeter_t(0) } },
        { { millimeter_t(-96) }, { millimeter_t(-48) }, { millimeter_t(0) } },
        { { millimeter_t(-94) }, { millimeter_t(-47) }, { millimeter_t(0) } },
        { { millimeter_t(-92) }, { millimeter_t(-46) }, { millimeter_t(0) } },
        { { millimeter_t(-90) }, { millimeter_t(-45) }, { millimeter_t(0) } },
        { { millimeter_t(-88) }, { millimeter_t(-44) }, { millimeter_t(0) } },
        { { millimeter_t(-86) }, { millimeter_t(-43) }, { millimeter_t(0) } },
        { { millimeter_t(-84) }, { millimeter_t(-42) }, { millimeter_t(0) } },
        { { millimeter_t(-82) }, { millimeter_t(-41) }, { millimeter_t(0) } },
        { { millimeter_t(-80) }, { millimeter_t(-40) }, { millimeter_t(0) } },
        { { millimeter_t(-78) }, { millimeter_t(-39) }, { millimeter_t(0) } },
        { { millimeter_t(-68) }, { millimeter_t(-29) }, { millimeter_t(10) } },
        { { millimeter_t(-58) }, { millimeter_t(-19) }, { millimeter_t(20) } },
        { { millimeter_t(-48) }, { millimeter_t(-10) }, { millimeter_t(30) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-38) }, { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(-39) }, { millimeter_t(0) }, { millimeter_t(39) } },
        { { millimeter_t(-40) }, { millimeter_t(0) }, { millimeter_t(40) } },
        { { millimeter_t(-41) }, { millimeter_t(0) }, { millimeter_t(41) } },
        { { millimeter_t(-42) }, { millimeter_t(0) }, { millimeter_t(42) } },
        { { millimeter_t(-43) }, { millimeter_t(0) }, { millimeter_t(43) } },
        { { millimeter_t(-44) }, { millimeter_t(0) }, { millimeter_t(44) } },
        { { millimeter_t(-45) }, { millimeter_t(0) }, { millimeter_t(45) } },
        { { millimeter_t(-46) }, { millimeter_t(0) }, { millimeter_t(46) } },
        { { millimeter_t(-47) }, { millimeter_t(0) }, { millimeter_t(47) } },
        { { millimeter_t(-48) }, { millimeter_t(0) }, { millimeter_t(48) } },
        { { millimeter_t(-49) }, { millimeter_t(0) }, { millimeter_t(49) } },
        { { millimeter_t(-50) }, { millimeter_t(0) }, { millimeter_t(50) } },
        { { millimeter_t(-51) }, { millimeter_t(0) }, { millimeter_t(51) } },
        { { millimeter_t(-52) }, { millimeter_t(0) }, { millimeter_t(52) } },
        { { millimeter_t(-53) }, { millimeter_t(0) }, { millimeter_t(53) } },
        { { millimeter_t(-54) }, { millimeter_t(0) }, { millimeter_t(54) } },
        { { millimeter_t(-55) }, { millimeter_t(0) }, { millimeter_t(55) } },
        { { millimeter_t(-56) }, { millimeter_t(0) }, { millimeter_t(56) } },
        { { millimeter_t(-57) }, { millimeter_t(0) }, { millimeter_t(57) } },
        { { millimeter_t(-58) }, { millimeter_t(0) }, { millimeter_t(58) } },
        { { millimeter_t(-60) }, { millimeter_t(0) }, { millimeter_t(60) } },
        { { millimeter_t(-62) }, { millimeter_t(0) }, { millimeter_t(62) } },
        { { millimeter_t(-64) }, { millimeter_t(0) }, { millimeter_t(64) } },
        { { millimeter_t(-66) }, { millimeter_t(0) }, { millimeter_t(66) } },
        { { millimeter_t(-68) }, { millimeter_t(0) }, { millimeter_t(68) } },
        { { millimeter_t(-70) }, { millimeter_t(0) }, { millimeter_t(70) } },
        { { millimeter_t(-73) }, { millimeter_t(0) }, { millimeter_t(73) } },
        { { millimeter_t(-76) }, { millimeter_t(0) }, { millimeter_t(76) } },
        { { millimeter_t(-79) }, { millimeter_t(0) }, { millimeter_t(79) } },
        { { millimeter_t(-83) }, { millimeter_t(0) }, { millimeter_t(83) } }
    };

    const LinePatterns& expectedPatterns = {
        { LinePattern::type_t::SINGLE_LINE, Sign::NEUTRAL,  Direction::CENTER },
        { LinePattern::type_t::JUNCTION_3,  Sign::NEGATIVE, Direction::LEFT   },
        { LinePattern::type_t::JUNCTION_3,  Sign::POSITIVE, Direction::CENTER }
    };

    test(linePatternDomain_t::Labyrinth, lineDetections, expectedPatterns);
}

TEST(LinePatternCalculator, LANE_CHANGE) {

    const LineDetections lineDetections = {
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } }
    };

    const LinePatterns& expectedPatterns = {
        { LinePattern::type_t::SINGLE_LINE, Sign::NEUTRAL,  Direction::CENTER },
        { LinePattern::type_t::LANE_CHANGE, Sign::POSITIVE, Direction::RIGHT  },
        { LinePattern::type_t::SINGLE_LINE, Sign::NEUTRAL,  Direction::CENTER }
    };

    test(linePatternDomain_t::Labyrinth, lineDetections, expectedPatterns);
}

TEST(LinePatternCalculator, LANE_CHANGE_noisy) {

    const LineDetections lineDetections = {
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) }, { millimeter_t(38) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } },
        { { millimeter_t(0) } }
    };

    const LinePatterns& expectedPatterns = {
        { LinePattern::type_t::SINGLE_LINE, Sign::NEUTRAL,  Direction::CENTER },
        { LinePattern::type_t::LANE_CHANGE, Sign::POSITIVE, Direction::RIGHT  },
        { LinePattern::type_t::SINGLE_LINE, Sign::NEUTRAL,  Direction::CENTER }
    };

    test(linePatternDomain_t::Labyrinth, lineDetections, expectedPatterns);
}