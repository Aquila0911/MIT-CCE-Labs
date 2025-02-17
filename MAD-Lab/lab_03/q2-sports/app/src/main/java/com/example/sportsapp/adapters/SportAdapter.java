package com.example.sportsapp.adapters;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.example.sportsapp.models.Sport;

import java.util.List;

public class SportAdapter extends RecyclerView.Adapter<SportAdapter.SportViewHolder> {
    private final List<Sport> sportList;
    private final OnSportClickListener onSportClickListener;

    public interface OnSportClickListener {
        void onSportClick(Sport sport);
    }

    public SportAdapter(List<Sport> sportList, OnSportClickListener onSportClickListener) {
        this.sportList = sportList;
        this.onSportClickListener = onSportClickListener;
    }

    @NonNull
    @Override
    public SportViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(android.R.layout.simple_list_item_1, parent, false);
        return new SportViewHolder(view);
    }

    @Override
    public void onBindViewHolder(SportViewHolder holder, int position) {
        Sport sport = sportList.get(position);
        holder.sportNameText.setText(sport.getName());
        holder.itemView.setOnClickListener(v -> onSportClickListener.onSportClick(sport));
    }

    @Override
    public int getItemCount() {
        return sportList.size();
    }

    public static class SportViewHolder extends RecyclerView.ViewHolder {
        TextView sportNameText;

        public SportViewHolder(View itemView) {
            super(itemView);
            sportNameText = itemView.findViewById(android.R.id.text1);
        }
    }
}
