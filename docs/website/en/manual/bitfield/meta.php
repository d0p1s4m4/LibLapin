<?php
$functions = [
  20 => [
    "t_bunny_bitfield",
    "bunny_new_bitfield",
    "bunny_delete_bitfield",
    "bunny_bitfield_set",
    "bunny_bitfield_get",
    "bunny_bitfield_clr",
  ],
  40 => [
    "t_bunny_auto_bitfield64",
    "t_bunny_auto_bitfield32",
    "t_bunny_auto_bitfield16",
    "t_bunny_auto_bitfield8",
    "bunny_auto_bitfield_set",
    "bunny_auto_bitfield_get",
    "bunny_auto_bitfield_clr",
    "bunny_new_abitfield",
  ]
];
foreach ($functions as $f => $l)
{
  foreach ($l as $k)
  {
    $circle_level[$k] = $f;
  }
}

$version_that_support = [
  "t_bunny_bitfield" => [11, $latest_version],
  "bunny_new_bitfield" => [11, $latest_version],
  "bunny_delete_bitfield" => [11, $latest_version],
  "bunny_bitfield_set" => [11, $latest_version],
  "bunny_bitfield_get" => [11, $latest_version],
  "bunny_bitfield_clr" => [11, $latest_version],
  "t_bunny_auto_bitfield64" => [11, $latest_version],
  "t_bunny_auto_bitfield32" => [11, $latest_version],
  "t_bunny_auto_bitfield16" => [11, $latest_version],
  "t_bunny_auto_bitfield8" => [11, $latest_version],
  "bunny_auto_bitfield_set" => [11, $latest_version],
  "bunny_auto_bitfield_get" => [11, $latest_version],
  "bunny_auto_bitfield_clr" => [11, $latest_version],
  "bunny_bitfield_set" => [11, $latest_version],
  "bunny_bitfield_get" => [11, $latest_version],
  "bunny_new_abitfield" => [11, $latest_version],
];
