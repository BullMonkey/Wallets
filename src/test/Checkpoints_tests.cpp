//
// Unit tests for block-chain checkpoints
//
#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/test/unit_test.hpp>
#include <boost/foreach.hpp>

#include "../checkpoints.h"
#include "../util.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(Checkpoints_tests)

BOOST_AUTO_TEST_CASE(sanity)
{
    uint256 p0 = uint256("0x3cdd9c2facce405f5cc220fb21a10e493041451c463a22e1ff6fe903fc5769fc");
    uint256 p1 = uint256("0x00000df334b33e08c9e10b351a4be5f5f11d0ce7c3b882150b0514174a23862a");
    BOOST_CHECK(Checkpoints::CheckHardened(0, p0));
    BOOST_CHECK(Checkpoints::CheckHardened(1, p1));

    
    // Wrong hashes at checkpoints should fail:
    BOOST_CHECK(!Checkpoints::CheckHardened(0, p1));
    BOOST_CHECK(!Checkpoints::CheckHardened(1, p0));

    // ... but any hash not at a checkpoint should succeed:
    BOOST_CHECK(Checkpoints::CheckHardened(0+1, p1));
    BOOST_CHECK(Checkpoints::CheckHardened(1+1, p0));

    BOOST_CHECK(Checkpoints::GetTotalBlocksEstimate() >= 1);
}    

BOOST_AUTO_TEST_SUITE_END()
