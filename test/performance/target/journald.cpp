// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2021 Joel E. Anderson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <benchmark/benchmark.h>
#include <cstdlib>
#include <stumpless.h>
#include "test/helper/fixture.hpp"
#include "test/helper/memory_counter.hpp"

NEW_MEMORY_COUNTER( function );

class JournaldFixture : public::benchmark::Fixture {
protected:
  struct stumpless_target *target;
  struct stumpless_entry *entry;

public:
  void SetUp( const ::benchmark::State &state ) {
    target = stumpless_open_journald_target( "journald-perf" );
    entry = create_entry(  );
    INIT_MEMORY_COUNTER( function );
  }

  void TearDown( const ::benchmark::State &state ) {
    stumpless_set_malloc( malloc );
    stumpless_set_realloc( realloc );
    stumpless_set_free( free );
    stumpless_destroy_entry_and_contents( entry );
    stumpless_close_journald_target( target );
    stumpless_free_all(  );
  }
};

BENCHMARK_F( JournaldFixture, AddEntry )( benchmark::State &state ) {
  for( auto _ : state ) {
    if( stumpless_add_entry( target, entry ) < 0 ) {
      state.SkipWithError( "could not send an entry" );
    }
  }

  SET_STATE_COUNTERS( state, function );
}
