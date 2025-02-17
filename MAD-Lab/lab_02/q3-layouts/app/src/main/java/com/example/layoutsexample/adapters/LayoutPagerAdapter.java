package com.example.layoutsexample.adapters;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentActivity;
import androidx.viewpager2.adapter.FragmentStateAdapter;

import com.example.layoutsexample.fragments.GridViewFragment;
import com.example.layoutsexample.fragments.ListViewFragment;
import com.example.layoutsexample.fragments.TableLayoutFragment;


public class LayoutPagerAdapter extends FragmentStateAdapter {

    public LayoutPagerAdapter(@NonNull FragmentActivity fragmentActivity) {
        super(fragmentActivity);
    }

    @NonNull
    @Override
    public Fragment createFragment(int position) {
        switch (position) {
            case 0:
                return new ListViewFragment();  // Fragment to display ListView
            case 1:
                return new GridViewFragment();  // Fragment to display GridView
            case 2:
                return new TableLayoutFragment();  // Fragment to display TableLayout
            default:
                return new ListViewFragment();
        }
    }

    @Override
    public int getItemCount() {
        return 3;  // 3 layouts to switch between
    }
}
