<div class="prototype">
  $Tunsigned long long@ $Sbunny_usleep@(
  $Tunsigned long long@ $Sdelay@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Wait until the sent delay expire. In microseconds.
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    The difference between the effectively wait time and the one that was
    requested. This may happen if a signal interrupt the program. In most
    case, 0 is returned.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_sleep</li>
  </ul>
</div>

